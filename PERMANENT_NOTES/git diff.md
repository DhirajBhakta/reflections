### Diff between 2 branches
```sh
git diff branch1 branch2
# same as
git diff branch1..branch2
```


### cherry-pick all commits between 2 branches
```sh
git cherry-pick branch1..branch2
```
Say
- you have a feature branch, which is rebased with `master` often.
- you have a `dev` branch which is largely polluted but everyone deploys their changes onto this branch.
- For some reason, you want the newer commits on your feature branch to be cherry-picked into this `dev` branch
```sh
git cherry-pick main..feat/myfeat
```
