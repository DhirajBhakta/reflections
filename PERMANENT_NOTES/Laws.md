## [Laws](https://github.com/dwmkerr/hacker-laws)

### Boy Scout Rule `tech-debt` `clean-code` `refactoring`
Always leave the code cleaner than you found it.

### Broken Windows Theory `tech-debt` `clean-code`

Poor code --> leads to---> more and more poor code.

Tech debt leads to a perception that efforts to improve quality may be ignored or undervalued, leading to more poor code.
This effect has a cascading effect ---> big ball of mud!

### Dunning-Kruger Effect `estimation`

People with low abilities are more likely to overestimate their abilities for the given task.

The less a person understands a domain, the more they are likely to believe they can easily solve problems in that domain.

Non-technical team members, or less experienced team members are more likely to underestimate the effort required to solve a problem.

### Parkinson's Law `estimation`

Work expands to fill all the time allotted to it.
Teams will be inefficient until deadlines loom near.

### Hofstadter's Law	 `estimation`
It always takes longer than you expect.
We are inherently bad at estimation, underestimating the effort more often than not.

### Hick's Law `estimation`
Decision time grows logarithmically to the number of options available, at worst, linear.

We tend to do binary search on ordered choices to reach the best option.

### Kernighan's Law `tech-debt` `clean-code`
Simple code is preferred over complex code. Debugging is twice as hard as writing code.

###  Unix Philosophy `clean-code`

### Chesterson's Fence `refactoring`
Reforms should not be made until the reasoning behind the existing state of affairs is understood.

>A man comes across a fence crossing the middle of the road. He complains to the mayor that this useless fence is getting in the way, and asks to remove it.
  The mayor asks why the fence is there in the first place. Man says he doesn't know. Mayor says "If you dont know its purpose, I certainly won't let you remove it.
  Go and find out the use of it, and then may I let you destroy it."

###  Dead Sea Effect 
More talented and effective IT engineers are the ones most likely to leave, to evaporate. Those who tend to remain behind are the residue, - the least talented.

###  Fitt's Law `ui-ux`

Time required to move to a target area is function of distance to the target divided by width of the target.

Interactive elements should be as large as possible, and distance b/w user's attention area and the interactive element should be as small as possible.

Group commonly used tasks as close as possible.

### Brook's Law `estimation`
Adding more people to a late software project,  delays it even more.
Coordination costs are deceptively high.

### Goodhart's Law
When a measure becomes a target, it ceases to be a good measure.

People will start optimizing for the measure, regardless of qualitative outcome
- number of lines of code
- code coverage percentage
- story points covered in sprint

### Hyrum's Law `backward compatibility`
_With a sufficient number of users of an API,
it does not matter what you promise in the contract:
all observable behaviors of your system
will be depended on by somebody._

be VERY STRICT about your API behavior, any foresight on some edge case misbehavior..might be used as a "feature" by some consumer  of your API and you will have a nightmare doing backward compatibility

### Conway's Law
Software structures/systems heavily reflect the already established organisational structure in the company.

Just because there are certain boundaries between org structures / teams, even the software systems will begin to mimic the same.

Be wary of this. Can have performance implications.

### Linus' Law
_Given enough eyeballs, all bugs are shallow_

This is why open source thrives. 

### Peter Principle
Competent people are promoted until the level where they are incompetent/not suited for.
