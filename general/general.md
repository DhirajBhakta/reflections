## [Laws](https://github.com/dwmkerr/hacker-laws)

### 0. Boy Scout Rule `tech-debt` `clean-code` `refactoring`
Always leave the code cleaner than you found it.

### 1. Broken Windows Theory `tech-debt` `clean-code`

Poor code --> leads to---> more and more poor code.

Tech debt leads to a perception that efforts to improve quality may be ignored or undervalued, leading to more poor code.
This effect has a cascading effect ---> big ball of mud!

### 2. Dunning-Kruger Effect `estimation`

People with low abilities are more likely to overestimate their abilities for the given task.

The less a person understands a domain, the more they are likely to believe they can easily solve problems in that domain.

Non-technical team members, or less experienced team members are more likely to underestimate the effort required to solve a problem.

### 3. Parkinson's Law `estimation`

Work expands to fill all the time allotted to it.

Teams will be inefficient until deadlines loom near.

### 4. Hofstadter's Law	 `estimation`
It always takes longer than you expect.

We are inherently bad at estimation, underestimating the effort more often than not.

### 5. Hick's Law `estimation`
Decision time grows logarithmically to the number of options available, at worst, linear.

We tend to do binary search on ordered choices to reach the best option.

### 6. Kernighan's Law `tech-debt` `clean-code`
Simple code is preferred over complex code. Debugging is twice as hard as writing code.

### 7. Unix Philosophy `clean-code`

### 8. Chesterson's Fence `refactoring`
Reforms should not be made until the reasoning behind the existing state of affairs is understood.

>A man comes across a fence crossing the middle of the road. He complains to the mayor that this useless fence is getting in the way, and asks to remove it.
The mayor asks why the fence is there in the first place. Man says he doesnt know. Mayor says "If you dont know its purpose, I certainly won't let you remove it.
Go and find out the use of it, and then may I let you destroy it."

### 9. Dead Sea Effect 
More talented and effective IT engineers are the ones most likely to leave, to evaporate. Those who tend to remain behind are the residue, - the least talented.

### 6. Fitt's Law `ui-ux`

Time required to move to a target area is function of distance to the target divided by width of the target.

Interactive elements should be as large as possible, and distance b/w user's attention area and the interactive element should be as small as possible.

Group commonly used tasks as close as possible.



## Something to digest early
Our industry is a young one. 

> This is something we seem to forget, and yet we have
only been creating programs that run on what we recognize as computers for around
70 years. Therefore, we are constantly looking to other professions in an attempt to
explain what we do. We aren’t medical doctors or engineers, but nor are we plumbers
or electricians. Instead, we fall into some middle ground, which makes it hard for
society to understand us, or for us to understand where we fit.
So we borrow from other professions. We call ourselves software “engineers,” or
“architects.” But we aren’t, are we? Architects and engineers have a rigor and disci
pline we could only dream of, and their importance in society is well understood. I
remember talking to a friend of mine, the day before he became a qualified architect.
“Tomorrow,” he said, “if I give you advice down at the pub about how to build some‐
thing and it’s wrong, I get held to account. I could get sued, as in the eyes of the law I
am now a qualified architect and I should be held responsible if I get it wrong.” The
importance of these jobs to society means that there are required qualifications peo‐
ple have to meet. In the UK, for example, a minimum of seven years study is required
before you can be called an architect. But these jobs are also based on a body of
knowledge going back thousands of years. And us? Not quite. Which is also why I
view most forms of IT certification as worthless, as we know so little about what good
looks like. <br/>
 &mdash; _Sam Newman, Building Microservices_

 - We create stuff thats designed to flex, adapt and evolve to user's changing requirements and as our understanding of the domain deepen, _unlike engineers and architects who already have a knowledge base of 1000+ years and create something static_
 - Pointless for the "architect" to create diagram after diagrams, pages and pages of documentation envisioning to create the __perfect__ system without taking into account the fundamentally unknowable future.
 - Our requirements shift faster than for engineers and architects. Even the tools and approaches shift faster
 - Our products are NOT never-changing-artifacts

 ### On "How to learn new things"
 1. Imitate the best until you get consistent results
 2. Understand why things work the way they do
 3. Learn to assign higher and lower values to different mindsets/aproaches/tech
 4. Create variations on best of ideas
 5. Innovate

 If you observe the normal way people learn, its usually the opposite. They learn very little and jump right on to do creative stuff. Some things work with trial and error, and you learn a thing or two...but youre just picking grains of sand on a desert


 #### Importance of Soft Skills!

 This is not obvious. Soft Skills are almost as important as your tech skills. They feed into your tech skills and empower you to get better at tech ultimately.

 You will NOT be sitting alone in a basement typing away in console. Shake away this stereotype. You WILL be dealing with humans, and humans are pretty more complex to deal with than any bug you've fixed. There will be times when you just want to be left alone to work productively, away from the nasty interruptions from mail/people/irritating DMs/"hey do you have a minute"/"hey can I get on a call with you" ... gritting your teeth wont do you any good.

 A company is a not that great place to be in, and feel chauvinistic about your work. Nearly everyone is there for the money, and you cannot convince them otherwise, and **you should not!**. We arent voluntarily there to achieve something collectively. Regardless of how they shiny HRs will sell you their "ideologies", "mission", "vision"... you'll realize this is just garbage, and noone really follows them. Nearly everyone treats it like a "forced" nine-to-five, and this atmosphere will turn you off sooner or later. .._Which is why you must attempt to have a taste of working in startups_, more on that later. You dont work solo, you work in a team. So please try to bring down your over enthusiastic drive in a project to achieve superhuman goals &mdash; there are other people working in the same team who would not want to work as fast, and would feel resentment towards you for creating an atmosphere of forced "over work". It might be "passion" for you..just for YOU, not them. Channel your energy in picking up new tech skills, digging deep into any topics of interest...anything that just involves you. These team members arent gonna be around with you forever in your career, so its wiser to channel your over enthusiastic energy towards something that reaps long term benefits.  
 
 Its pretty hard to swallow that " No job is worth dying for", especially after how hard you've worked to get here. If it is too much to do and the company is not hiring more hands to solve the problem. Do not put it on your own shoulders to try to work harder and longer. It will only end up with you getting burnt out. Be smart about when it is time to go home. You can lose years for the stupidity of shouldering a problem that not yours to handle alone. Just think about the hours lost ( say 3 hours per day x 365 = ~1000 hours a year. Infact, if youre clever about it you can spend 6 hours daily honing your skills , gaining mastery over new topics every 2 years! Just think about the sunk cost)

A lot of the time your tech skills will be secondary. Social skills are prime. Dont be that person who knows a lot, works a lot, but is very difficult to work with. For every such person who actually manages to succeed, there are 1000s of other such people whose careers were shattered on the rocks...._just because theyre difficult to work with_.

You wont always get a chance to do things PERFECTLY. Sometimes you have to accept tech debt, in favour of business' interests. Keep harmony in the team. 
 - Working peacefully in a team
 - handling friction within teammates
 - Negotiating for your salary
 - Staying professional, not getting emotional
 - Finding ways to cope with ideas of your teammatchauvinistices(higher up or lower down) that you do not agree with.
 - Get good at quickly judging competence of your people, their styles, and come up with tailored approach to deal with them
 - How to speak to them without making them defensive


#### T shaped skillset _techinically_
![](https://miro.medium.com/max/924/1*3jJEfx1B2xX86Uc1_e0r1Q.png)

> You can never understand everything. But you should push yourself to understand the system
    - _Ryan Dhal, nodejs_
- A little bit about everything. Broads idea of the field. The big picture
- Become an expert in one thing. Be really really good, with unimaginable depth.

Why have the breadth? Oftentimes you'll notice havoc "somewhere" in the system but do not know where! Othertimes, you'll sorta know _okay, its some networking issue_ , _oh it seems be some OS issue_ . DO NOT BE THIS GUY! Knowing a little bit of everything isnt impossible. You can do some priliminary investigation of the problem yourself without waiting on some other guy/team and claiming it to be a blocker.

At the very least, have enough knowledge to communicate to the specialized team the problem you're facing in the most detail as you possibly can.
"Help me ! this is not working" is very VERY annoying

be the T shaped developer. Do not be in a position where you have absolutely no clue about the subject being talked about. If you find yourself in such scenarios, feel the damn guilt and go read the fundamentals within a week.

Ignorance = incompetence = reeks disgust

’ve been in more than one organization where the various groups within IT feel very frustrated with each other. Conflicting priorities and overly rigid or excessively porous boundaries lead to conflict, which causes bad feelings or, worse, lots and lots of meetingswhere everything gets painfully negotiated and still more processes get piled on everyoneuntil absolutely all progress chokes on ceaseless paperwork.

Who’s responsible for fixing or, better still, preventing this mess?You are.So is your coworker.So is the person you’ve sworn an unbreakable blood oath of eternal vengeance against.Managers cannot improve interpersonal reactions. Managers can impose formalstructure, and bad management can make things even worse, but even a good managercan’t make two clashing personalities work together without imposing lots of formality.But if an argument just keeps looping over and over the same ground, it’s time tochange the rules.The quickest way to change a person’s reactions to you is by earning their respect. Thequickest way to earn an IT person’s respect is to demonstrate intelligence and competence.
#### Act like a professional
If you want to be taken seriously, you must act like a professional
- no gossips, backstabbing




## Role of the Architect
 - An architect cannot and should not _overspecify_ things to the last detail. Rather make the framework where changes can smoothly happen.
 - A software architect should be more like a town planner than an actual architect. 
 - sets only the direction, and direct involvement is minimal. But like the town-planner, if the sewage plant is being developed in the residential area, then he needs to step in to shut it down.
 - Make the environment _habitable_ for developers
 - Should know how to _Zone_. And worry less about what happens inside the zones, and worry more about what happens between the zones.
    - Worry how services across the zones talk to each other.
    - How to monitor the health of each of the services in each of the zones
    - If teams use microservices, architect trusts the team to make the right local decisions.
    - _Be worried about what happens between the boxes, than what happens inside_ : If one team uses REST over HTTP, another uses Java RMI, gRPC, protocol buffers...communication becomes nightmare! standardize this!
    - Its one thing to give the teams the freedom to choose the stack for their microservice and another to make teams so varied that moving developers across becomes impossible, and we dont have grasp of a particular technology as a company. We also wont be able to build solutions spanning all the teams ( eg: logging, monitoring) 
    Netflix, for example, has mostly standardized on Cassandra as a data-store technology. Although it may not be the best fit for all of its cases, Netflix feels that the value gained by building tooling and expertise around Cassandra is more important than having to support and operate at scale multiple other platforms that may be a better fit for certain tasks . See?
- How to monitor the overall health of the system
    - System-wide view, not a service-specific view
    - All services should emit health and general monitoring related metrics in a same standard way
    - **Push mechanism** Where every service _pushes_ data to central location.
- Define integration styles
    - REST over HTTP? standardize it across all services.
    - define the concepts of noun, verb for REST endpoints
    - define to how handle pagination of resources in REST terms
    - Define how the downstream services will interpret your service's output. HTTP status codes 2XX 4XX 5XX to be defined perfectly || proper standardized messages within the output
    - Knowing the difference between a request that was OK and processed correctly, a request that was bad and thus prevented the service from doing anything with it, and a request that
    might be OK but we can’t tell because the server was down is key to ensuring we can fail fast and track down issues. If our services play fast and loose with these rules, we end up with a more vulnerable system.
    - Refrain from making microservice interfaces being too chatty --> will lead to performance issues.

- sit with the team regularly and pair program to get a sense of how the team works ( effective than having a call or reviewing code)
- Understand Company's **Strategies**
    - Eg: goal is to decrease time to market on new features.
- Define **Principles**
    - note that principles are different from constraints
    - They try to achieve the company strategies
    - Eg: to decrease time to market, the principle is that delivery teams have full control over the lifecycle of of their s/w to ship whenever they are ready, not blocked by any other team.
- Define **Practises** that adhere to the principles
    - Eg: All logging should happen centrally
    - Eg: REST/HTTP is the standard integration style
    - Due to their technical nature, practises tend to change more than principles
- After defining the standards, principles and practises, make it easy for the developers to follow them.. dont make it a burden.
    - Write a real-world _exemplar_ service (which is actually running in PROD in the company) which follows all the principles, practises. New devs love imitation.
    - You can write the _boilerplate_ for each microservice, or something that generates the boilerplate. Eg; `arc-react-tools`, `arc-react-boilerplate`, `phoenix` as tomcat wrapper, `arda` as flask boilerplate
        - Common stuff like health checking, exposing metrics exposing HTTP endpoints etc can be inside this boilerplate
        - If you write the boilerplate and make it mandatory, you also need to worry about how to _upgrade_ this boilerplate in already running microservices !
- If you are working in an organization that places lots of restrictions on how developers can
do their work, then microservices may not be for you.




# Fail Fast Philosophy | Defensive Programming | Assertive Programming
https://www.martinfowler.com/ieeeSoftware/failFast.pdf

_Lets suppose that the preconditions are not met and if so, fail quickly._

> Write your preconditions/invariants for your function at the top of its body,
before it does its actual thing. So that, even if its called..it will check its conditions and stop dead if they are not met.

_Suspect all invalid conditions, throw the appropriate exception, ..and do it early...before doing a lot of computations, which will anyway fail_

We are used to (even encouraged to) "continue as if nothing happened", and keep the execution going without blocking any flows. This is just hiding the dirt under the carpet and not solving the real problem.
...And when issues occur, we are forced to investigate the logs to find where exactly the failure occurred.

The longer it takes for a bug to appear on the surface, the longer it takes to fix and the greater it costs.

Usually the bug goes around and causes a lot of side effects causing 100 other bugs, hiding the root cause. Had you failed fast when the first bug occurred, you could fix it faster.

This **Continue as if nothing happened** approach is the root cause of firefighting during go live.



### What do we generally do when stuff fails
- delay the failure
- fail silently
- handle the failure and move on
- **fail fast**

#### What is "Robust" anyway?
Should you really "automatically" handle all your errors? Should you really bang your head thinking about workarounds? Even if you do..how sure are you that that particular workaround will not cause multiple hard-to-find bugs much later.

Doing exactly the opposite, i.e not handling the errors and letting it fail the system EARLY on actually makes it more robust! That way, atleast you will know very quickly when an error occurs and know exactly where

Bugs that are easer to find and fix = fewer bugs that go into production.

Failing fast is non-intuitive way to make your system more robust.


## Robust over Performant
Code that fails fast, might look like its slow, less performant.

But you rather have a robust system than a performant system 9/10 times.
Also, dont believe the "It will slow it down" BS unless you have proper profiling results. Check what the true penalty is with a proper benchmark.

_When faced with doubts about performance penalties, the forceful response must be certain evidence of significant degradation._

## Examples
1. Catch exceptions ONLY when you know what to do with it. Or dont catch at all.
**We should not** swallow exceptions.
1. When an env variable required for startup is missing, we should immediately abort the startup and report the issue.
  **We should not** let the startup happen anyway and continue as if nothing happened.

2. If we get Invalid request parameters, we should fail with 400 BAD_REQUEST.
**We should not** try to correct the params and continue the request.





## When selecting a new Tech, 
 ### Measure the **Technical Fit**
 [RAD-Cert Philosophy](https://rad-cert.com/Home/Philosophy)
 - Does this help with the problem?
 - Is there something that will help us more?
 - How does it compare against competitors?
 - Is this the simplest thing we can do?
 - Does it bring unnecessary costs?
 - Is there extra maintenance?
 - Does it have good documentation?
 - Does it have good developer community acceptance?


# My Learnings
## For a greenfield project 
- Get [The walking skeleton](https://www.oreilly.com/library/view/97-things-every/9780596800611/ch60.html) up and ready as the first priority
- DONT aim to make the perfect architecture in first shot.
- Write basic tests and automate the process of running those tests locally.
- Automate the deployment process (but with ability to be triggered manually)
- Setup CICD ASAP



## Continuous Delivery
- Every _check-in_ is a release candidate.
  
## Hexagonal Architecture 
pass

## Onion Architecture
Has a lot of layers, and makes you cry when you try to cut through it.

## Links 
[Notes to myself on software engineering](https://medium.com/s/story/notes-to-myself-on-software-engineering-c890f16f4e4d)
