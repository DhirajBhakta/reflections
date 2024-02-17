Make sure you're connected to the internet
```sh
ip addr
# If you want to connect over wifi.. 
iwctl
> device list
> station wlan0 scan
> station wlan0 get-networks
> station wlan0 connect "JioFiber"

ip addr # confirm if wlan0 got an IP address
ping google.com
```

Synchronize time with  NTP server...
```sh
timedatectl set-ntp true
timedatectl status
```

## Preparing the disk

Partition the disk
```sh
fdisk -l
fdisk /dev/sda
> g # create a GPT partition table
# /dev/sda1 --> 500M boot partition (EFI System)
# /dev/sda2 --> 12G swap partition (Linux Swap)
# /dev/sda3 --> 64G root partition (Linux Root)
# /dev/sda4 --> 400G home partition (Linux Home)
```

Format the partitions
```
mkfs.fat -F32 /dev/sda1
mkswap /dev/sda2
swapon /dev/sda2
mkfs.ext4 /dev/sda3
mkfs.ext4 /dev/sda4
```

Mount the partitions
```sh
mount /dev/sda3 /mnt
mount /dev/sda4 /mnt/home
```

Generate the fstab file... The fstab file tells the bootloader what the partitions are and how to mount them, at boot time.
```sh
genfstab -U /mnt >> /mnt/etc/fstab
```


## Installing Archlinux

Install base packages.
```sh
pacstrap /mnt base base-devel linux linux-firmware
```

chroot into /mnt (jail)
```sh
arch-chroot /mnt
```

Setup networking (and wireless networking)
```sh
pacman -S networkmanager wpa_supplicant wireless_tools netctl
systemctl enable NetworkManager
```

Set locale and hostname
```sh
vim /etc/locale.gen
# uncomment en_US.UTF-8
locale-gen

echo "AMATERASU" >> /etc/hostname
cat << EOF > /etc/hosts
> 127.0.0.1     localhost
> ::1.          localhost
> 127.0.1.1     AMATERASU.localdomain  AMATERASU
```

Set root password
```sh
passwd
```

Create primary user
```sh
useradd -m -g users -G wheel dhirajbhakta
passwd dhirajbhakta
pacman -S sudo
visudo # uncomment WHEEL all all
```


## Installing GRUB
```sh
pacman -S grub efibootmgr dosfstools mtools os-prober
mkdir /boot/EFI
mount /dev/sda1/ /boot/EFI
grub-install --target=x86_64-efi \
  --bootloader-id=grub_uefi \
  --recheck \
  --efi-directory=/boot/EFI \ #optional
grub-mkconfig -o /boot/grub/grub.cfg
```

Fully installed at this point. Exit and reboot 

---
