# mido_fbcon

hacked up branch from forked mido-m-oss from provided XiaoMi vendor kernel

Everyone has these forked kernels but no one has decent readmes for what they are.

This is a silly attempt to get a framebuffer console on XiaoMi's Redmi Note 4 (probably 4x?)  It's from the mido-m-oss branch.

The hack is in mido_fbcon branch here.

Note that the kernel doesn't actually completely boot, and even the official (not compiled, provided with phone) kernel has numerous boot errors if you check dmesg.  Still working on that.  Remember to get the right branch.

I still have a ways to with this but hopefully it's helpful to someone, especially since I think some HuaWei phones also use MSM stuff.

## What it took to get the framebuffer console:

I don't have one of those fancy debugging cables you hook to the board, those are like a couple grand I think.  Instead, this took me almost two weeks of booting the phone, blindly messing with the graphics drivers without so much as an error message, flashing them to the phone and seeing if anything worked.

## Preface:

So first, there's some compiler breakers in the branch, silly stuff.

Then, MSM is Qualcomm's "Mobile Station Modem", pretty useless acronym.

Then they've got MDDI, Mobile Display Digital Interface.  So, you're saying that the graphics have an interface?  Really?  And it's digital?  You don't say.  There's probably five engineers at Qualcomm that actually do any work and the rest just sit around and come up with silly acronyms.

MHL has something to do with the phone streaming 4K content through the phone to your TV.  If you're into that sort of thing...

MDSS and DSI are I think both about MIPI Display Serial Interface, well, yeah... same thing, these acronyms are all totally useless.  But that's why they get paid the big bucks at Qualcomm while I'm broke.

## The hack:

The major thing here is that there are seemingly two different framebuffer video drivers but the mdss one is missing fb_imageblit, etc,. that fbcon needs in order for the framebuffer console to draw to the screen.  And the other MSM framebuffer video driver doesn't seem to compile, it wants the MDSS_COMMON config setting otherwise you get undefined references.  Basically there's a bunch of MSM/MDSS video stuff in there and it's also linked into other things I think with the SoC (another silly acronym, I think "system on chip").

And then somehow, you have to take the framebuffer back from the bootloader, the fastboot thing, otherwise it keeps that fastboot splash image until the kernel has booted up and, I think, the framebuffer has been written too twice.  But it's not totally clear what the deal here is.  I have to mess with it a bit more.

blank_blank turns the screen off, blank_unblank turns it on

I thought the overlay stuff was something to do with a particular write mode, to handle parts of an operating system... i.e., like when you hit the power button and it draws whatever over the screen to ask you if you want to turn the phone off.  But now I'm not so sure.  dma_fnc pointer also points to something to setting up the dma which may or may not be necessary.

A big thing is that when register_framebuffer is called, it needs something to write to, so I added the silly google ion dma crap in there.  I'm sure there's a more standard linux dma that really should be used.  So that's "screen_base".  The fbi stuff, is the framebuffer info, various info passed around.

After register_framebuffer is called, the fbcon or whatever almost immediately does fb_open to open the framebuffer device.  Unfortunately, there's some kind of problem with pm_runtime.  And I don't know whether this is the hack or not.  It seems like in parts of fb_probe, pm_runtime errors are just ignored, like it's not set up properly or something.  I don't know, something is off with that and I guess it works later?  But so fb_open tries to turn the phone "on" using pm_runtime but disable_depth is set as if the phone has been turned off twice, and this is while the screen is on, no idea, I just skipped it.

Similarly the framebuffer console, console, etc., call fb_set_par to set the screen resolution, etc.. Something in there doesn't work, I don't know, maybe the dma has to be reallocated andd reset, maybe it's something else.  But I just return -1 and skip it.  Not so great.  I think this is the most serious thing to fix since it will be used by user space later I think.

There's also something with fbcon... it sets FB_ACTIVATE_NOW and the MSM drivers don't like this, they like FB_ACTIVATE_VSYNC I think.  I'm not sure I know the details, it's something to do with when the screen is written to or something, I don't know.  Doesn't seem important.  No but seriously, I think some of this stuff never worked in this provided kernel.

And then there's printk... the one provided with the kernel had some kind of console locking problem.  Again, I don't know how this ever worked, it looked like it was locking the console and then calling vt, or something which then again called console_lock and, like it was double locking, it was a mess, so I took the recent 4.13.2 linux kernel release printk, and pasted it in there.

And then, another thing that, probably means something but I don't know what... printk looks for some ttyS stuff early on, for early boot, but then later, it wants tty, not ttyS, and it looks for console=tty0, etc,. etc.. But if you use this, it conflicts with something and nothing works, I should know, but at this point I was kind of running out of care.  So I cut out the console strcmp in printk so that if a console is passed to printk in register_console or whatever, it's good to go.

Additionally, there's some extended console stuff from recent kernels that I had to cut out as well as potentially some kind of rate limit denial of sevice vulnerability, maybe... not sure... 

I'm using console=flibbertygibbit0 on my command line to indicate that really something else should be there.  Also the command line is forced because the bootloader does something, I'm not sure.  It wants some selinux thing or some androidboot setting, something silly, so I got tired of messing with it when making recovery images and just forced it in the kernel compile.

And then back to the MSM drivers, they like to call "wait_event_timeout"... and I wasn't real sure why this was a problem because presumably there's some separate display thread that's just notified of an update from the dma or something?  But it causes problems because it seems like it's within some scheduling lock somewhere or something, I don't know.  So wait_for_kickoff and pan_idle both call these waits, and I just have them exit.  I mean yeah, this is a total hack.

Lastly, it seems like it tries to register an fb1 for some reason, I don't know, this is another probably major issue like set_par, but I add something to have it just do the one fb0.

And yes, I did this all without a debugger or any error messages.

## Compiling:

I used the linaro compiler chain, there's a little build script I put in the directory there, no silly repo nonsense, or other trees, etc.. It's just a kernel.

I've set it up to do cat Image.gz *.dtb > Imagedtb since the kernel make scripts weren't really compiling the open firmware device blobs.

The device blobs themselves I stripped from the provided with phone kernel with https://github.com/dianlujitao/split-appended-dtb

Making the recovery image which I used to boot without overwriting the boot/system images on the phone, (although somehow it messed up my primary boot anyway, probably thinks that something has been altered) was done with scripts from my incomplete https://github.com/peterius/LFM and the android mkbootimg pythong script... I think it likes the word "ANDROID" at the start or something.

## Last notes:

I hope this is useful to someone and will add more when I get it working better.
