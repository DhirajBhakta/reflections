https://www.youtube.com/watch?v=TlbcAphLGSc. https://www.youtube.com/watch?v=TV8SyEuSMIA
agents are autonomous executors who plan, execute, and complete a task.
And this is what an Agent is:  capable of reasoning, planning, and interacting with its environment**. We call it Agent because it has _agency_, aka it has the ability to interact with the environment.
```py
memory = [user_defined_task]
while llm_should_continue(memory): # this loop is the multi-step part
    action = llm_get_next_action(memory) # this is the tool-calling part
    observations = execute_action(action)
    memory += [action, observations]
```
So this system runs in a loop, executing a new action at each step (the action can involve calling some pre-determined _tools_ that are just functions), until its observations make it apparent that a satisfactory state has been reached to solve the given task. Here’s an example of how a multi-step agent can solve a simple math question:
<img src="https://huggingface.co/datasets/huggingface/documentation-images/resolve/main/transformers/Agent_ManimCE.gif"/>

![[agents-00.png]]
To make agents reliable, you need to carefully configure them for a specific business process, and that's where AI Agent developers come in. your role is to ensure that your agents have access to all the necessary resources, tools, and knowledge to perform their tasks.
1. Conducting thorough business research and determining what resources the agent will need
2. Creating tools (as I said, they are the most important when creating an agency)
3. Constant iteration, gathering feedback from stakeholders, and adjusting in a cycle until the agent is stable
4. Deploying agents and integrating them into the client's business so that they work smoothly with employees

## history
https://www.youtube.com/watch?v=OFS90-FX6pg
![[agents-01.png]]
  boom in gaming industry -> GPU -> researchers realized it is ideal for neural networks

RNNs ... made bigger and bigger RNNs...LSTM

transformer arch ("attention is all u need") :This architecture, based on the attention mechanism, allowed models to better understand the context in data sequences, which is especially important for natural language processing.... Unlike previous approaches, transformers could efficiently process long sequences of words, taking into account the connections between elements remote from each other. This paved the way for creating models capable of understanding and generating texts indistinguishable from those written by humans.
![[Pasted image 20250512221759.png]]

......
![[Pasted image 20250512221723.png]]



### Agentic design patterns
- reflection
- tool use
- planning and reasoning
- multi agents





### Special tokens to define structured blocks

Each LLM has some **special tokens** specific to the model. The LLM uses these tokens to open and close the structured components of its generation. For example, to indicate the start or end of a sequence, message, or response. Moreover, the input prompts that we pass to the model are also structured with special tokens. The most important of those is the **End of sequence token** (EOS).

The forms of special tokens are highly diverse across model providers.

The table below illustrates the diversity of special tokens.

|**Model**|**Provider**|**EOS Token**|**Functionality**|
|---|---|---|---|
|**GPT4**|OpenAI|`<\|endoftext\|>`|End of message text|
|**Llama 3**|Meta (Facebook AI Research)|`<\|eot_id\|>`|End of sequence|
|**Deepseek-R1**|DeepSeek|`<\|end_of_sentence\|>`|End of message text|
|**SmolLM2**|Hugging Face|`<\|im_end\|>`|End of instruction or message|
|**Gemma**|Google|`<end_of_turn>`|End of conversation turn|
### system prompt
When using Agents, the System Message also **gives information about the available tools, provides instructions to the model on how to format the actions to take, and includes guidelines on how the thought process should be segmented.**

# 65 hr genai bootcamp

###  prompt must be elaborate 
https://github.com/omenking/free-genai-bootcamp-2025/blob/main/sentence-constructor/claude/prompt.md notice how 
- a lot of supplementary documents are referenced in the system prompt. 
- a document containing lots of good and bad examples 
- a section explaining the state machine states. Elaboration on each state.



![[agent-00.jpeg]]


--- 
# Materials 
- https://ampcode.com/how-to-build-an-agent
- https://github.com/huggingface/smol-course 
- https://huggingface.co/learn/llm-course 
- https://huggingface.co/learn/agents-course
- https://huggingface.co/learn/mcp-course
- https://www.learn-agents.diy/intro
- https://youtu.be/DOXJ7s1D6iE?si=fseG6EFBrnIayf1a (65HRS)
- distillation: https://www.linkedin.com/posts/armand-ruiz_the-nvidia-pruning-and-distillation-paper-activity-7330185754129637376-ET9m?utm_source=share&utm_medium=member_ios&rcm=ACoAABxgSw0BpU7CKu8JjFcYWAJCI325-os5ow8
- gh repos
	- https://github.com/MODSetter/SurfSense cheatcode = notebooklm
	- crawl4ai)agenticrag)  https://github.com/unclecode/crawl4ai https://docs.crawl4ai.com/advanced/multi-url-crawling/   https://github.com/coleam00/ottomator-agents/tree/main/crawl4AI-agent https://www.youtube.com/watch?v=FQlCWrsUpHo https://www.youtube.com/watch?v=_R-ff4ZMLC8
	- unstract https://unstract.com/
	- lightrag  https://github.com/HKUDS/LightRAG knoledge graoh and https://github.com/getzep/graphiti realtime ingestiohn
	- mem0 https://docs.mem0.ai/faqs#how-does-mem0-work
	- chonkie https://chonkie.ai/ goddamn!! rag helper!!
	- https://github.com/567-labs/instructor structured outputs although langgraphs trustcall https://github.com/hinthornw/trustcall 
	- https://github.com/NirDiamant/RAG_Techniques
	-  https://github.com/pengfeng/ask.py/blob/main/ask.py#L751 - rag barebones.
   https://www.anthropic.com/news/contextual-retrieval    https://arxiv.org/html/2408.04948v1.  https://www.youtube.com/watch?v=mQt1hOjBH9o (agentic rag)
- rag basics to adv
	- https://www.youtube.com/watch?v=BrUW8_cCTew 
	- https://www.youtube.com/watch?v=_R-ff4ZMLC8 agentic rag
	- https://www.reddit.com/r/Rag/comments/1k5e6oz/my_document_retrieval_system_outperforms/
	- https://www.reddit.com/r/Rag/comments/1ig66e6/deepseeks_boost_your_rag_chatbot_hybrid_retrieval/
	- https://www.reddit.com/r/Rag/comments/1jjkvpp/building_document_search_for_rag_for_2000/ 
	- https://www.reddit.com/r/ChatGPTCoding/s/5HdxDjkNn9 Repo graphic improves rag.
	- https://www.reddit.com/r/ChatGPTCoding/s/msweMo53Lg RAG hurts coding agents...wutt
	- https://cocoindex.io/blogs/index-code-base-for-rag/ 
	- https://blog.lancedb.com/rag-codebase-1/
	- https://www.linkedin.com/posts/aniketmish_building-a-prod-grade-llmrag-system-is-hard-activity-7333008896816545793-BMyi?utm_source=share&utm_medium=member_ios&rcm=ACoAABxgSw0BpU7CKu8JjFcYWAJCI325-os5ow8
	- https://www.linkedin.com/posts/armand-ruiz_%F0%9D%97%95%F0%9D%98%82%F0%9D%97%B6%F0%9D%97%B9%F0%9D%97%B1%F0%9D%97%B6%F0%9D%97%BB%F0%9D%97%B4-%F0%9D%97%94%F0%9D%97%9C-%F0%9D%97%AE%F0%9D%97%B4%F0%9D%97%B2%F0%9D%97%BB%F0%9D%98%81%F0%9D%98%80-%F0%9D%97%B6%F0%9D%98%80-%F0%9D%9F%B1-activity-7327649109383749632-65pa?utm_source=share&utm_medium=member_desktop&rcm=ACoAABxgSw0BpU7CKu8JjFcYWAJCI325-os5ow8 𝗕𝘂𝗶𝗹𝗱𝗶𝗻𝗴 𝗔𝗜 𝗮𝗴𝗲𝗻𝘁𝘀 𝗶𝘀 𝟱% 𝗔𝗜 𝗮𝗻𝗱 𝟭𝟬𝟬% 𝘀𝗼𝗳𝘁𝘄𝗮𝗿𝗲 𝗲𝗻𝗴𝗶𝗻𝗲𝗲𝗿𝗶𝗻𝗴.
	- https://www.youtube.com/watch?v=TO2R4aKsfes rag expert https://www.youtube.com/watch?v=wexpoR1R03A He says fine tuning LLM model is pointless but fine tuning an embedding model, finetuning reranker... is far better.cuz it mproves search.... build cheap fast eval loops, ditch llm as judge approach....If you see a table while parsing a file or a pdf parse the table and index it separately into another postgres table. https://github.com/ksm26/Embedding-Models-From-Architecture-to-Implementation   https://huggingface.co/blog/train-sentence-transformers
	> Ok, for large text docs you likely want a hierarchical semantic chunking strategy that can support clustering. Idea is you have smaller chunks for sentences, paragraphs, and bigger chunks for pages that point to the smaller chunks. Then with retrieval, you start with the bigger chunks and work your way down to smaller. As for embedding, you’ll likely need 2, one for the bigger chunks and one for the smaller. Then, you’ll like want to do hybrid storage where you store the chunk, along with important metadata in the vectordb, that way when you do get a chunk you also have access for the data. As for the parsing and decomposition of the document I would recommend something that can take a PDF and produce a json description off all the content and components. From there, add intelligent post processing

arcana: https://www.youtube.com/watch?v=-rsTkYgnNzM&t=59s madness csv ingestion..
- https://www.ibm.com/downloads/documents/gb-en/12f5a71117cdc329