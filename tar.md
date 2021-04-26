

# Archival vs Compression

Archival is just shoving a directory(s) into one file.

Compression, &mdash; using mathematical trickery to save space. Archival DOESNT save space.

So what's the point of archiving if it doesnt save space? think FTP, zillions of files nested under thousands of folders, enormous number of FTP calls to query "Hey which dir? whats inside this dir..."so on... frikkin rabbit hole. So many calls saved if all this crap was in one archive file

# tar
"tape archive"

### archive + compress
` tar -cvzf docs.tar.gz Documents/  `

c : create the archive
v : verbose
z : gzip compression

### unarchive + decompress
` tar -xvzf docs.tar.gz`



## tarbomb horror
dont send an archive with hundreds of files
` tar -cvzf ../tarbomb.tar.gz .  `
Notice the dot, youre essentially tarring all files at the top level. Think how this tar can blow up on the face of the guy who unarchives it. Think of the number of files getting overwritten maybe.

dont do it

just tar the CONTAINING folder so taht it vomits just one folder, and he has to dig deeper for the files
`tar -cvzf notATarbomb.tar.gz wrapperFolder/`

this is called being nice