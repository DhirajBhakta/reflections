![](https://www.redhat.com/cms/managed-files/ci-cd-flow-desktop_1.png)

# Goal?
our  goal  as  software  professionals  is  to  deliver  useful,  working software to users as quickly as possible.

to do this,
we need to make **frequent**, **automated** releases of our software

 a  release  process  that  is  repeatable,  reliable,  and  predictable, which in turn generates large reductions in cycle time, and hence gets features and bugfixes to users fast.

_have multiple developers working simultaneously on different features of the same app._

use of deployment pipelines, combined with high levels  of  automation  of  both  testing  and  deployment  and  comprehensive configuration  management  to  deliver  push-button  software  releases.  That  is, push-button software releases to any deployment target—development, test, or production.
# Definitions

**Continuous Integration**:Executable  code  changes  when  a  change  is  made  to  the  source  code.  Every time a change is made to the source code, the resulting binary must be built and tested. In order to gain control over this process, building and testing the binary should be automated. The practice of building and testing your application on every  check-in  is  known  as  continuous  integration; 

**Nightly Build**:

**Rolling Build**:

**Deployment Pipeline** : an automated implementation of your application’s build, deploy, test, and release process.

**Configuration Management** : being able to repeatably re-create every piece of in-frastructure used by your application. That means operating systems, patch levels, OS  configuration,  your  application  stack,  its  configuration,  infrastructure configuration,  and  so  forth  should  all  be  managed.  You  should  be  able  to  re-create your production environment exactly, preferably in an automated fashion.

**Version Control**: Source control is just for source code. 

VCS is for having everything related to your project in a version control repository 
- all assets, artifacts.
- all requirement documents,..by PMs
- release plans, progress charts... by PMs
- all test scripts etc ..by testers 
- all info required to re-create production, test envts (think of IaaC)
- It is even helpful to keep the configuration files for the development team’s development environ-ments in version control since it makes it easy for everyone on the team to use the same settings

**Working s/w app**: can be usefully decomposed into four components: executable  code,  configuration,  host  environment,  and  data. 

**Deming cycle**: plan, do, study, act. for continuous improvement. Have a retrospective on what can be improved, and assign one person per idea to own it until next restrospective meet.

**"Ultimate Configurability"** : The  desire  to  achieve  flexibility  may  lead  to  the  common  antipattern  of “ultimate configurability” which is, all too frequently, stated as a requirement for software projects. It is at best unhelpful, and at worst, this one requirement can kill a project.

Jez Humble, David Farley

- Developers
- Testers
- Operations

**How do the following fit together**?
configuration management, automated testing, continuous integration and  deployment,  data  management,  environment  management,  and  release management
### CI done right, but CD sucks
You have code, it compiles, and all the unit tests pass on your continuous integration server, but it takes a couple of days to release the new version into the publicly accessible UAT environment

# Deployment Antipatterns

### Deploying Manually
- Detailed doc, how-to guides just for deployment
- Manually testing everything after release

**Instead**
1. Deployment should be fully automated
2. Human intervention only for -> choosing the env and hitting the "Deploy" button

Everything is explicit in a script. Automated deployment scripts are better up-to-date documentation of your deployment process.

### Deploying to "production-like-env" only after development is "complete"
- The very first release into PROD env, is likely to be the most cumbersome.. Things you never saw before, pop up..and release date is fast approaching.
- There is too much disparity between Staging and PROD

**Instead**
Get the walking skeleton on PROD ASAP, even if its just a humble hello world. Be battle ready close to release deadline.

Test environments should closely resemble your production environments in terms of software configuration—that way there should be no surprises when you deploy to production.This does not imply that test environ-ments must be clones of expensive production environments; rather, that they should be managed, deployed to, and configured by the same mechanisms 

### Manual Config Mgmt for Prod
- Directly changing config on PROD
- unable to roll back to older, working set of config

**Instead**
Config should be version controlled

<hr/>

A working s/w app has
- executable code
- config
- host envt
- data

**A change in any one of the above** will make the app behave differently

### Change in Executable code
- if source code changes
    - (Trigger CI:) then the binary must be **built** and **tested** (automated ofc)
    - One executable(binary) for all envts (PROD, uat, test). Different config for diff envts.
    -  If your system uses a compiled language, you should ensure that the binary output of your build process—the executable code—is reused everywhere it is needed and never rebuilt.


### Change in Config
- Different config for diff envts
    - Anything that changes b/w envts has to be captured as config. (same binary executable tho)
    - 
### Change in Host envt
- change in OS, shared libs, networking stack etc and stuff, needs to be tested
pass
### Change in Data
pass


### -> Checklist after change <--
1. **(BUILD Phase)** The process of creating the executable code must work. This verifies that the syntax of your source code is valid.
2. **(TEST Phase)** The  software’s  unit  tests  must  pass.  This  checks  that  your  application’s code behaves as expected
3. **(TEST Phase)** The software should fulfill certain quality criteria such as test coverage and other technology-specific metrics.
4. **(TEST Phase)** The software’s functional acceptance tests must pass. This checks that your application  conforms  to  its  business  acceptance  criteria—that  it  delivers the business value that was intended.
5. **(TEST Phase)** The software’s nonfunctional tests must pass. This checks that the application performs sufficiently well in terms of capacity, availability, security, and so on to meet its users’ needs.
6. **(TEST Phase)** The software must go through exploratory testing and a demonstration to the customer and a selection of users. This is typically done from a manual testing environment. In this part of the process, the product owner might decide that there are missing features, or we might find bugs that require fixing and automated tests that need creating to prevent regressions.

_The environments these tests run in must be as similar as possible to production, to verify that any changes to our environments have not affected the application’s ability to work._


# Configuration management

**Principles**
- Keep executable separate from configuration
- Keep all config in one place ( for all applications, envts )

**Can you answer "yes" to these?**
1. Could you completely re-create your production system, excluding production data, from scratch from the version-controlled assets that you store?
2. Could you regress to an earlier, known good state of your application?
3. Can you be sure that each deployed environment in production, in staging, and in test is set up in precisely the same way?

## How do you represent your configuration information?
- Configuration = list of key value pairs
- where to keep it?
    - version controlled repo ( use git-secrets if its a secret )
    - DB
    - registry, directory
## How do your deployment scripts access it?
Its best to have a config server centralized for all applications (remember Zookeeper based "CODEX" in Arcesium and DEShaw?) ([Sprint Cloud config](https://soshace.com/centralize-the-configuration-of-services-with-spring-cloud-config/))

get configuration. Params?
- application_name
- environment

Applications can perform an HTTP GET which includes the application and environment name in the URI to fetch their configuration. This mechanism makes most sense when configuring your application at deployment time or run time. You pass the environment name to your deployment scripts (via a property, command-line switch, or environment variable), and then your scripts  fetch  the  appropriate  configuration  from  the  configuration  service  and make it available to the application, perhaps as a file on the filesystem.

Whatever the nature of the configuration information store, we recommend that you insulate the detail of the technology from your application with a simple façade class providing a `getThisProperty()` `getThatProperty()` style of interface, so you can fake it in tests and change the storage mechanism when you need to. (agnostic interface)

`getConfig( application_name, environment )`

**Configuration management of every application should be planned as part of project inception.** Consider how other applications in your ecosystem manage their configuration and use the same method, if possible. Too often, decisions on how to manage configuration are done on an ad-hoc basis, and as a result every application packages its configuration in a different place and uses a different mechanism for accessing it. This makes it unnecessarily hard to determine the configuration of your environments.

## Types of Configuration
- build time config (**bad practice**)
- package time config
- installation time config (just before/after binary is placed where its supposed to go)
- run time config

build time config is bad bcos, same binary/executable should be used in all envts. Anything that changes between envts need to be captured as configuration and NOT baked in when the application is compiled or packaged.

> One serious problem with the J2EE specification is that the configuration has to be packaged in the war or ear along with the rest of the application. Unless you use another configuration mechanism instead of that provided by the specification, this means that you have to create a different war or ear file for every environment that  you  deploy  to  if  there  are  any  configuration  differences.  If  you  are  stuck with this, you need to find another way to configure your application at deployment time or run time. 

Solution?:
 (Make your app fetch the config over HTTP or something at run time..from a remote config server)

 (check in all config in git repo, encrypt using git-secrets, decrypt it before build time)

## Testing configuration
<u>Config changes need to be tested</u> with the applications that consume them

Ensure that you have tests for your configuration that are run at deployment or installation time. Check that the services your application depends upon are available, and use smoke tests to assert that any functionality depending on your configuration settings works as it should.

## Managing Environments
Make the envt creation a fully automated process.

 It should always be cheaper to create a new environment than to repair an old one. Being able to reproduce your environments is essential for several reasons.
 - be able to create copies of PROD envt...for testing purposes maybe
 - be able to re-create the PROD envt...because repair of existing one takes time
 - to NOT be in a condition where only one guy knows how to set up, and then he goes on a leave, leaves the firm

 (tldr; commit your terraform Iaac code to your repo)

you should treat your environment the same way you treat your code—changing it incrementally and checking the changes into version control.Every  change  should  be  tested  to  ensure  that  it  doesn’t  break  any  of  the applications that run in the new version of the environment.



# Continuous Integration
The goal of continuous integration is that the software is in a working state all the time.

http://www.jamesshore.com/v2/blog/2006/continuous-integration-on-a-dollar-a-day

Continuous integration requires that every time somebody commits any change, the entire application is built and a comprehensive set of automated tests is run against it. Crucially, if the build or test process fails, the development team stops whatever they are doing and fixes the problem immediately. 

Running the application in a local development environment should  use  the  same  automated  processes  that  are  used  in  the  continuous integration and testing environments and ultimately in production.
Prereqs?: 
1. you should be able to **build** and **test** your app with commandline
2. Automated test suite.
    - otherwise , "success" means just that the code could be compiled without syntax errors.


# Questions
- What is Pupper, CHef, Ansible...