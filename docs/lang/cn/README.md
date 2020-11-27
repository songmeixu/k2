<div align="center">
<img src="https://raw.githubusercontent.com/sequeender/k2/main/docs/logo.png" width=376>

<p align="center">
  <a href="https://github.com/sequeender/k2/tree/main/docs#k2">English</a> |
  <span>中文</span> |
  <a href="https://github.com/sequeender/k2/tree/main/docs/lang/kr#k2">한국어</a> |
  <a href="https://github.com/sequeender/k2/tree/main/docs/lang/sp#k2">Español</a> |
  <a href="https://github.com/sequeender/k2/tree/main/docs/lang/fr#k2">Français</a> |
  <a href="https://github.com/sequeender/k2/tree/main/docs/lang/ru#k2">Pусский</a>
</p>

---

[![Documentation Status](https://readthedocs.org/projects/k2/badge/?version=latest)](https://k2.readthedocs.io/en/latest/?badge=latest)

</div>



##  k2 了解一下

###### :hatching_chick:   什么是 k2 ?

如果你稍微了解过人工智能在语音领域的开源解决方案，很可能你已经知道 kaldi。而k2，在设想目标中，将其作为kaldi 的进化版本，所以称之为 k2（我们的确没在命名上花费时间，未来很可能会改名，就像 caffe->caffe2->part of pytorch的过程）。目前工作于小米的@dpovey，作为全职开发人员，主导 k2的开发工作。



###### :8ball:   k2 怎样实现目标?

这里有@dpovey 的回答，但如果你想要彻底理清头绪可能有点困难，因为整个开发目前还在进行中，文档对开发者都还不健全。不如让我先简单的对k2怎样具备下一代语音框架的潜质解释一下。在 kaldi 的建模过程中，有许多基于假设的理论算法、以及追求性能的工程优化（比如对hmm拓扑结构、音素上下文、独立并简化的语言模型），如今受上一代的框架的限制，不仅趋近其准确率的上限、而且工程应用方面在物联网趋势下又存在躲不掉的性能障碍。所以为了扩展框架上的视野，我们初步的设想是，

- **理论算法上**
  - 摆脱繁复的搭积木式的建模、搭的越高积累的错误也越多，尽量直接从序列化的数据中学习。
  - 使用对序列建模友好的、计算理论成熟的、且可实现图灵完备程序的有限状态接受机（FSA），对数据输入和输出建模。
  - 需要将原有的语言模型通过更现代的方式结合建模。
- **工程实现上**
  - 优化算法：采用在神经网络上验证了自身性能的梯度优化算法，来对语音的各个任务相关的序列损失函数（已有：LF-MMI、CTC）进行优化。
  - 数据结构：采用在神经网络上已广泛使用的 tensor 概念，不过要考虑序列数据的特性以及计算的粒度分布而重新定义。
  - 结合已有框架：目前，已通过[dlpack](https://github.com/dmlc/dlpack) 使自定义tensor 在c++层与 pytorch的tensor 通信，且通过 pybind11暴露一致的 python 接口到 pytorch 的 python 层。这样，就可以利用 pytorch 的已有功能（如：数据 pipeline、分布式训练、部署推断）。



###### :shell:   ​欢迎参与 k2 的发展！

如上所述，我们还没发布面向用户的版本，还处在需要 contributors 来一同开发、甚至拓展 k2的定义。

- 如果你是开源爱好者、任一方面有开发能力，参与贡献的方式为：通过阅读/提出/参与 issues 讨论，以及通过 PRs 贡献代码。
- 我们基本上通过 github/issue 交流，如果有沟通需要，欢迎加入[非官方飞书群](https://go.feishu.cn/JQAh1F5/)，与开发者们一起探讨。
- 如果在中国的你，恰好正在寻找一份全职工作，得益于小米对开源的支持，Daniel 的团队对人才的大门长开（以我所见，目前团队不会野蛮扩张， 以代码能力为首要，尤其青睐编程达人、 GPU 或嵌入式高性能计算人才，至于语音算法方面不必有专业背景。也许最好的让大家认识你的方式是向 official [k2](https://github.com/k2-fsa/k2.git) repo 提交代码。）



---



## k2 的启动代码

###### :octocat:   编译开发

```bash
git clone https://github.com/sequeender/k2.git
cd k2
bash build.sh # There are instructions for each steps
```



###### :bullettrain_side:   使用

```bash
pip install k2-nailuo 
# "k2-nailuo" is used to distinguish this repo from "k2" of 
# the official [k2-fsa/k2](https://github.com/k2-fsa/k2.git)
```

```python
import k2_nailuo
k2_nailuo.FSA()
```



######  :crab:   尝尝螃蟹腿

这里部署了一个可以直接展示部分已完成的功能的 [google colab]().