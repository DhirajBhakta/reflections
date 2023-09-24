
## RHEL
- `rpm` is the package manager for RHEL and Centos.
- `yum` is the preferred user-friendly package manager for RHEL and Centos. `yum` uses `rpm` under the hood, hiding its complexities.
- `dnf` is the successor of `yum`. 

## Debian
- `dpkg` is the package manager for Debian and its derivatives like Ubuntu.
- `apt` is the preferred user-friendly package manager for Debian and its derivatives. `apt` uses `dpkg` under the hood, hiding its complexities.

#### Adding new repo
"repo" is a logical collection of packages. 

If you need to install packages from a unofficial repo, you need to first download the **PGP keyring** of that repo. For eg:
```sh
curl -fsSL https://pkgs.k8s.io/core:/stable:/v1.28/deb/Release.key | sudo gpg --dearmor -o /etc/apt/keyrings/kubernetes-apt-keyring.gpg
```
Keyring contains public keys of the packages in the repo. This is to make sure that you can validate the authenticity of the package by verifying the signature of the package when you pull them.
Then add a file with a single line  to `/etc/apt/sources.list.d/`
```bash
echo 'deb [signed-by=/etc/apt/keyrings/kubernetes-apt-keyring.gpg] https://pkgs.k8s.io/core:/stable:/v1.28/deb/ /' | sudo tee /etc/apt/sources.list.d/kubernetes.list
```
Run `sudo apt-get update` to update the apt package index.
You can now install the packages from this repo with `apt-get`. 
```sh
sudo apt-get install -y kubelet kubeadm kubectl
```

## Arch Linux
- `pacman` is the package manager for Arch Linux.
- `yay` or `yaourt` etc are package managers for installing packages from AUR. 
- official repos `core` , `extra` have prebuilt binaries for packages, whereas AUR does not (would have blown up), and hosts only the PKGBUILDs of packages.

pacman does NOT build the package from source. pacman just downloads the prebuilt binaries from the repos(mirrors).

If not using pacman, the approach to installing a package should be by building from source
1. look up the PKGBUILD file(package description) and learns where the source code is,
2. pull the source code, 
3. run `makepkg -Si` in a fakeroot(chroot)
4. run `pacman -U ` on the result

`makepkg` is a wrapper for doing 
```sh
# 3 step build process adopted by most authors. 
./configure
make
make install
```
But often the build steps/instructions can be different, and `makepkg` looks up these instructions from the PKGBUILD

#### PKGBUILD
a shell script run by(needed by) `makepkg`  to build the package into a binary executable. It contains instructions on how to build the package.

#### "Repository"
is a logical collection of packages, physically stored on multiple mirrors. `core` , `extra` and `multilib` are "official" repositories, `AUR` is unofficial repository. 

#### Validating authenticity of a package
"Is this package really coming from a trusted source?". How does it know who to trust in the first place? pacman maintains a **keyring** - a collection of PGP keys to check signed packages. These are public keys from official repositories. This keyring is refreshed regularly. 
The keyring is stored at `/etc/pacman.d/gnupg`.

#### AUR
Equivalent to PPAs in debian.
Unlike `core` , `extra` or `multilib` (official repositories), AUR repository doesn't host prebuilt binaries/packages. It just hosts PKGBUILD files for every package.

`pacman` cannot lookup PKGBUILD files from the AUR (Arch User Repositories). You need to manually download the PKGBUILD for the required package in AUR, read the PKGBUILD file to get the URL for obtaining source code, download the source code, run `makepkg`  to compile the source , ....and then run `pacman -U ` on the result to install the binary to appropriate location (in PATH). 

AUR helpers like `yay` act like `pacman` but for AUR. 


