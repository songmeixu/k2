<div align="center">
<img src="https://raw.githubusercontent.com/sequeender/k2/main/docs/logo.png" width=376>

<p align="center">
  <span>English</span> |
  <a href="https://github.com/sequeender/k2/tree/main/docs/lang/cn#k2">中文</a> |
  <a href="https://github.com/sequeender/k2/tree/main/docs/lang/kr#k2">한국어</a> |
  <a href="https://github.com/sequeender/k2/tree/main/docs/lang/sp#k2">Español</a> |
  <a href="https://github.com/sequeender/k2/tree/main/docs/lang/fr#k2">Français</a> |
  <a href="https://github.com/sequeender/k2/tree/main/docs/lang/ru#k2">Pусский</a>
</p>

---

[![Documentation Status](https://readthedocs.org/projects/k2/badge/?version=latest)](https://k2.readthedocs.io/en/latest/?badge=latest)

</div>



## A description of k2

###### :hatching_chick:   What's k2?

If you have a knowledge of the open source solutions about speech artificial intelligence, it is likely that you already know [Kaldi](https://github.com/kaldi-asr/kaldi). Therefore, this project, as an evolutionary version of Kaldi in the early assumptions, is called k2 (we did not spend time on naming, as it is likely to be renamed in the future, may like the process of "caffe-&gt;caffe2-&gt;part-of-pytorch").



###### :8ball:   How does it work?

Here is @dpovey's [answer](ABOUT.md), it may be a bit difficult if you want to clarify your clues completely, because the entire development is still in progress and the documentation is not sound yet. Let me briefly explain how k2 has the potential of the next-generation speech framework. In Kaldi’s modeling process, there are many theoretical algorithms based on assumptions and performance-oriented engineering optimizations (such as hmm topology, phoneme context, independent and simplified language models). Nowadays, they are limited by the previous generation of frameworks. It is approaching the upper limit of its accuracy rate, and there are performance obstacles that cannot be avoided under the IoT trend in engineering applications. So in order to expand the horizon on the framework, our initial assumption is,

- **In terms of theoretical algorithms**
  - Get rid of complex building-block modeling. The higher you build, the more errors you accumulate. Instead, try to learn directly from sequence data.
  - Widely use the finite state acceptor (FSA), which is sequence-friendly and with mature computational theory. As the finite state machine can realize Turing complete program, it's supposed to lose nothing in its usage of modeling sequence data input and output. 
  - In k2 new framework, the language model is expected to be accomplished in a modern way.
- **In terms of engineering implementation**
  - *Optimization algorithm*: The gradient optimization algorithm that has verified its performance on the neural network is used to optimize the sequence loss functions related to speech tasks (existing: LF-MMI, CTC). 
  - *Data structure*: The tensor concept that has been widely used in neural networks is adopted, but it must be redefined in consideration of the characteristics of sequence data and the granularity distribution of computations. 
  - *Combining with the existing framework*: At present, benefit from [dlpack](https://github.com/dmlc/dlpack), the custom tensor can pass data with the tensor of pytorch in c++ layer. And the consistent python interface is exposed as pytorch python API through [pybind11](https://github.com/pybind/pybind11). In this way, pytorch's existing functions (such as data pipeline, distributed training, deployment inference) can be exploited.



###### :shell:   ​Who can get involved with the project today？

As mentioned above, we have not yet released a user-oriented version, and we still need contributors to develop together and even expand the definition of k2.

- If you are an open-source enthusiast and have development capabilities in some aspect, participating in the contribution is through reading/posting/replying issues and making PRs.
- To communicate through GitHub/issue is applicable. But if you would like to join in random chat with developers and others, here is also an unofficial [Feishu](https://go.feishu.cn/JQAh1F5/) group.
- If you happen to be looking for a full-time job in China, Daniel’s team opens the door to you (thanks to Xiaomi’s support to open-source). (Ps, In my opinion, the current team will not expand brutally. Skilled programmers, GPU/embedded high-performance computing talents are especially favored. There is no need to have a professional background in speech algorithms. Maybe the best way to introduce yourself is by contributing to the official [k2](https://github.com/k2-fsa/k2.git) repo.)



---



## A instruction for how to build, use, and have a taste

###### :octocat:   build

```bash
git clone https://github.com/sequeender/k2.git
cd k2
bash build.sh # There are instructions for each steps
```



###### :bullettrain_side: ​  use

```bash
pip install k2-nailuo # "k2-nailuo" is used to distinguish this repo from "k2" of the official [k2-fsa/k2](https://github.com/k2-fsa/k2.git)
```

```python
import k2_nailuo
k2_nailuo.FSA()
```



###### :crab:   taste

Here is a [google colab](https://colab.research.google.com/drive/1qbHUhNZUX7AYEpqnZyf29Lrz2IPHBGlX?usp=sharing) shows some completed functions.

