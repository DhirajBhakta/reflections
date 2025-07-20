Running `git gc` often helps "pack" up your objects into delta compressed format, saving space.

### `git fsck`
_a healthcheck_
Check if you have unreachable objects (orphaned/dangling)
```sh
$ git fsck

dangling tree 8276318347b8e971733ca5fab77c8f5018c75261
dangling blob 2302a5a4baec369fb631bb89cfe287cc002dc049
dangling blob cb54512d0a989dcfb2d78a7f3c8909f76ad2326a
dangling tree 8e1088e1cc1bc67e0ef01e018707dcb07a2a562b
dangling blob 5e069ed35afae29015b6622fe715c0aee10112ad
```

which you can then prune with `git prune -n`
