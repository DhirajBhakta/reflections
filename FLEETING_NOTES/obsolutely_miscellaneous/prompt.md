

## Concepts
### Temperature
controls randomness and creativity or surprise. _More hallucination_

### Top P
"Top Percentage"

If TopP=80%, then the "next word" generated will be picked up from top 80% of the most probable words.

More the TopP, more the creativity. Less the TopP, more the predictability and conservativeness.

#### Prompt by example
```
Question: what is the capital of USA?
Answer: The Capital of [USA] is:(Washington)

Question: what is the capital of Australia?
Answer: 
```

#### Giving a Role
((**Role**)) ((**Detailed Context with Who What Where When Why How**)) ((**If you have any questions, ask me**))

The last bit will help you to provide far more detailed context.

```
You are an expert in viral youtube titles. Think of catchy and attention-grabbing
titles that will encourage people to click and watch the video. The titles should be short,
concise and direct. They should also be creative and clever. Try to come up with titles
that are unexpected and surprising. Do not use titles that are too generic or titles 
that have been used too many times before. If you have any questions about the video, 
ask before you try to generate titles.
```

#### "Ignore all previous instructions before this one..."
To reset .

#### "...Explain everything step by step"
- "_Lets think step by step_"
- "_Explain like im 5_"

phrases like "step by step" is called Zero-Shot-Chain-Of-Thought

#### Plan and solve
```
...Lets first understand the problem and devise a plan to solve the problem.
Then, Let's carry out the plan and solve the problem step by step.
Calculate intermediate results , pay attention to calculation and common sense.
```
