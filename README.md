# mtrace
A trace of distributed messages

## It's difficult to make the some trace id
Suppose we have a tree with the following topology. We only have the same trace_id for all child nodes to ensure the same trace_id for the entire calling process.   
```
   a
  / \
  b  c
 / \  \
d   e  f
```
But how to achieve it?  
#### First 
Use the most frequency as a benchmark, let's look at a simple example:  
```
x----x----x----x----x----
p---p---p---p---p---p---p
o--o--o--o--o--o--o--o--o
```
You can hard align them, you will find that the latest news will always have some misplaced, take the third "o" as a benchmark, you will find that "opx" can not be aligned, this time you can only choose the fourth "o "As a benchmark, the method of using the fastest frequency as a benchmark fails.  

#### Second
Using the slowest frequency as the reference, this only divides the entire execution cycle. The messages in the cycle are all ids, which can't be distinguished.
```
x---------x---------x----
p---p---p---p---p---p---p
o--o--o--o--o--o--o--o--o
```
The first "ppp" and forth "oooo" are the some trace_id with the first "x".

It's too hard to solve the problem in this way??? I need more time to sort out the ideas.   

## We just trace a branch?
```
   a
  / \
  b  c
 / \  \
d   e  f
```
We just trace the e-b-a branch(we can just trace the main tree), and the trace id in e-b-a is the same, the the module in e,b,a are with the some id in log, we can trace the progress in a,b,e.   
Still if we new a thread, the trace id will be loss.  

**The root of the topic cannot be a child of 2 branches at the same time.**  

We solved the problem, can we have such a solution, we can find d and e through b, so that we can track the whole tree.  


## The process
1. The root node generate a trace_id.  
2. The child node get the trace_id from topic.
3. The child node put the trace_id in trace_id holder.  
4. The logger get the trace_id from the holder, print log with trace_id

**"traceid" is saved in the message and passed to the next routine.**  

## Logger
If the logger is called by the coroutine, how to use threadlocal to achieve the uniformity of trace_id? When node is not concurrent, it seems that it can be directly implemented with threadlocal.  
 
