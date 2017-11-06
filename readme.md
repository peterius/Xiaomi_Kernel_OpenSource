# mido_fbcon

hacked up branch from forked mido-m-oss from provided XiaoMi vendor kernel

Everyone has these forked kernels but no one has decent readmes for what they are.

This is a silly attempt to get a framebuffer console on **XiaoMi's Redmi Note 4 (probably 4x?)**  It's from the **mido-m-oss** branch.

The hack is in **mido_fbcon** branch here.

Note that even the official (not compiled, provided with phone) kernel has numerous boot errors if you check dmesg.

I still have a ways to go with this but hopefully it's helpful to someone, especially since I think some HuaWei phones also use MSM stuff.

I don't know, there's a bunch of msm stuff all over the web, but who knows what works with what.

I'm currently attempting to get configfs and functionfs working, the android stuff is just unnecessary.  But I was surprised at how poor the development state of even the latest functionfs is so I'm still working with that.

## Compiling:

I used the linaro compiler chain, there's a little build script I put in the directory there, no silly repo nonsense, or other trees, etc.. It's just a kernel.

I've set it up to do something like ** cat Image.gz *.dtb > Imagedtb ** since the kernel make scripts weren't really compiling the open firmware device blobs.

The device blobs themselves I stripped from the provided-with-phone boot.img kernel with https://github.com/dianlujitao/split-appended-dtb

Making the recovery image which I used to boot without overwriting the boot/system images on the phone, (although somehow it messed up my primary boot anyway, probably thinks that something has been altered) was done with scripts from my incomplete https://github.com/peterius/LFM and the android mkbootimg python script... I think it likes the word "ANDROID" at the start or something

## Last notes:

**boot_delay=500** to read messages

I hope this is useful to someone and will add more when I get it working better.
