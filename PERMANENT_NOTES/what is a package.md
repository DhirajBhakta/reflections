Just a **tar** containing
- a binary executable
- metadata: version, description
- man page
- configuration file(s)
- information about dependencies
- README

For example, this is the content of `vi` package in arch linux
```
-   usr/
-   usr/bin/
-   usr/bin/edit
-   usr/bin/ex
-   usr/bin/vedit
-   usr/bin/vi
-   usr/bin/view
-   usr/lib/
-   usr/lib/ex/
-   usr/lib/ex/expreserve
-   usr/lib/ex/exrecover
-   usr/share/
-   usr/share/licenses/
-   usr/share/licenses/vi/
-   usr/share/licenses/vi/LICENSE
-   usr/share/man/
-   usr/share/man/man1/
-   usr/share/man/man1/edit.1.gz
-   usr/share/man/man1/ex.1.gz
-   usr/share/man/man1/vedit.1.gz
-   usr/share/man/man1/vi.1.gz
-   usr/share/man/man1/view.1.gz
-   var/
-   var/lib/
-   var/lib/ex/
```

Every linux distribution (or specifically, the package manager) has its own package format.
- Debian created `.deb` package format
- RHEL created `.rpm` package format
- Arch linux uses pacman, which uses "zipped tar"(`bsdtar`) format. Pretty simplistic. 


> Its PRECOMPILED. No need to "build" from source. You already have the executable in the archive(tar). 

