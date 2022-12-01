---
title: 领域驱动设计
date: 2021-01-03 19:47:03
updated:
copyright: true
password:
mathjax: true
---
### 领域驱动设计目的

DDD帮助我们拆解需求，并建立一个***灵活性高、可扩展***的业务系统

领域驱动设计中的领域是什么？我理解的是一个比行业更加细分的方向，比如互联网做电商业务是电商领域，电商中有专注交易的交易领域，做电子支付叫支付领域。领域范围可大可小，领域知识表示某些具有相关相关性知识的合集。

领域驱动设计是通过领域知识构建的领域模型来控制业务的复杂性，通过领域模型反映领域知识，构建更易维护的系统。解决软件难以理解，难以演化的问题。

### 领域驱动设计的核心价值

领域驱动设计的核心目标是基于特定业务范围，通过统一业务概念（统一语言），将系统参与各方整合在一起，从而减少不同角色和环节的信息熵减问题。

领域模型是领域驱动设计的核心产出，它不仅能描述真实的业务逻辑和业务场景，也是系统实现的表达方式。领域模型的适应性能直接反应系统的扩展性上，能否使系统在增大时仍然保持敏捷。

领域驱动设计之所以更加流行，**很大因素是领域驱动设计提供的方法论上与近些年流行的微服务有很好的匹配性**，通过领域驱动设计方法清晰地**识别业务边界，以此来指导微服务的拆分**。 领域驱动设计提供的领域划分方法可以指导我们对微服务的拆分，以及对于演进式架构有很强的助力。

![四层架构](https://noogel.xyz/resource/img/2022-01-19-00-07-56.png)

![概念的涵盖范围](https://noogel.xyz/resource/img/2021-12-12-18-59-11.png)

『领域的边界划分不断演绎，只要发现复杂性凝聚的地方，就划定为有界上下文，割裂它与其他系统的关系，并派出精兵强将专门对付。』

![](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9hdGEyLWltZy5jbi1oYW5nemhvdS5vc3MtcHViLmFsaXl1bi1pbmMuY29tLzNkMTYxNTlkOTUxNTYwYmQwMDA2Y2ZlNzEwODNlNjdiLnBuZw)

复用性是告诉我们When（什么时候该下沉了），即有重复代码的时候。内聚性是告诉我们How（要下沉到哪里），功能有没有内聚到恰当的实体上，有没有放到合适的层次上（因为Domain层的能力也是有两个层次的，一个是Domain Service这是相对比较粗的粒度，另一个是Domain的Model这个是最细粒度的复用）。




![](https://imgconvert.csdnimg.cn/aHR0cHM6Ly9hdGEyLWltZy5jbi1oYW5nemhvdS5vc3MtcHViLmFsaXl1bi1pbmMuY29tLzZlMGM3OTEwZDgwYmE3ZDUyNWNjYzM5ZmUwMmI0MmYyLnBuZw)

领域服务(DomainService)

上面我们讲述了各个要素对于资源和行为的封装，业务逻辑的实现代码应该尽量放在聚合根边界内。但是总会遇到不适合放在聚合根上的业务逻辑，而此时领域服务就需要承载编排组合领域对象、资源库和防腐接口等一系列要素，提供对其它上下文的交互接口。

防腐层

用来消除外部上下文结构差异的作用，也叫适配层。比如在算价上下文中需要调用促销上下文数据，不同的促销数据源提供了不同的接口和数据，这时就需要引入防腐层来屏蔽差异，防止外部上下文侵入领域内部影响代码模型。首先定义需要的数据接口规范。


参考：

https://www.cnblogs.com/wlandwl/p/ddd_five.html

https://www.cnblogs.com/pyer/p/15856573.html

https://blog.csdn.net/significantfrank/article/details/98087611

---


Domain Primitive

Domain Primitive 是一个在特定领域里，拥有精准定义的、可自我验证的、拥有行为的 Value Object 。

（1）将隐性的概念显性化
（2）将 隐性的 上下文 显性化
（3）封装 多对象 行为

▍什么情况下应该用 Domain Primitive
常见的 DP 的使用场景包括：

有格式限制的 String：比如Name，PhoneNumber，OrderNumber，ZipCode，Address等

有限制的Integer：比如OrderId（>0），Percentage（0-100%），Quantity（>=0）等

可枚举的 int ：比如 Status（一般不用Enum因为反序列化问题）

Double 或 BigDecimal：一般用到的 Double 或 BigDecimal 都是有业务含义的，比如 Temperature、Money、Amount、ExchangeRate、Rating 等

复杂的数据结构：比如 Map<String, List<Integer>> 等，尽量能把 Map 的所有操作包装掉，仅暴露必要行为

---

在做架构设计时，一个好的架构应该需要实现以下几个目标：


独立于框架：架构不应该依赖某个外部的库或框架，不应该被框架的结构所束缚。

独立于UI：前台展示的样式可能会随时发生变化（今天可能是网页、明天可能变成console、后天是独立app），但是底层架构不应该随之而变化。

独立于底层数据源：无论今天你用MySQL、Oracle还是MongoDB、CouchDB，甚至使用文件系统，软件架构不应该因为不同的底层数据储存方式而产生巨大改变。

独立于外部依赖：无论外部依赖如何变更、升级，业务的核心逻辑不应该随之而大幅变化。

可测试：无论外部依赖了什么数据库、硬件、UI或者服务，业务的逻辑应该都能够快速被验证正确性。


数据存储层

Account   本质上是一个 Entity 
``` java
@Data
public class Account {
    private AccountId id;
    private AccountNumber accountNumber;
    private UserId userId;
    private Money available;
    private Money dailyLimit;

    public void withdraw(Money money) {
        // 转出
    }

    public void deposit(Money money) {
        // 转入
    }
}
```
AccountRepository 是一层抽象

```java

public interface AccountRepository {
    Account find(AccountId id);
    Account find(AccountNumber accountNumber);
    Account find(UserId userId);
    Account save(Account account);
}

public class AccountRepositoryImpl implements AccountRepository {

    @Autowired
    private AccountMapper accountDAO;

    @Autowired
    private AccountBuilder accountBuilder;

    @Override
    public Account find(AccountId id) {
        AccountDO accountDO = accountDAO.selectById(id.getValue());
        return accountBuilder.toAccount(accountDO);
    }

    @Override
    public Account find(AccountNumber accountNumber) {
        AccountDO accountDO = accountDAO.selectByAccountNumber(accountNumber.getValue());
        return accountBuilder.toAccount(accountDO);
    }

    @Override
    public Account find(UserId userId) {
        AccountDO accountDO = accountDAO.selectByUserId(userId.getId());
        return accountBuilder.toAccount(accountDO);
    }

    @Override
    public Account save(Account account) {
        AccountDO accountDO = accountBuilder.fromAccount(account);
        if (accountDO.getId() == null) {
            accountDAO.insert(accountDO);
        } else {
            accountDAO.update(accountDO);
        }
        return accountBuilder.toAccount(accountDO);
    }

}

```

Account实体类和AccountDO数据类的对比如下：

Data Object数据类：AccountDO是单纯的和数据库表的映射关系，每个字段对应数据库表的一个column，这种对象叫Data Object。DO只有数据，没有行为。AccountDO的作用是对数据库做快速映射，避免直接在代码里写SQL。无论你用的是MyBatis还是Hibernate这种ORM，从数据库来的都应该先直接映射到DO上，但是代码里应该完全避免直接操作 DO。

Entity实体类：Account 是基于领域逻辑的实体类，它的字段和数据库储存不需要有必然的联系。Entity包含数据，同时也应该包含行为。在 Account 里，字段也不仅仅是String等基础类型，而应该尽可能用上一讲的 Domain Primitive 代替，可以避免大量的校验代码。

DAO 和 Repository 类的对比如下：

DAO对应的是一个特定的数据库类型的操作，相当于SQL的封装。所有操作的对象都是DO类，所有接口都可以根据数据库实现的不同而改变。比如，insert 和 update 属于数据库专属的操作。

Repository对应的是Entity对象读取储存的抽象，在接口层面做统一，不关注底层实现。比如，通过 save 保存一个Entity对象，但至于具体是 insert 还是 update 并不关心。Repository的具体实现类通过调用DAO来实现各种操作，通过Builder/Factory对象实现AccountDO 到 Account之间的转化

原有的TransferService不再包括任何计算逻辑，仅仅作为组件编排，所有逻辑均delegate到其他组件。这种仅包含Orchestration（编排）的服务叫做Application Service（应用服务）。

![overview](https://mmbiz.qpic.cn/mmbiz_png/33P2FdAnjuibCA7zuzhlSIpEHAClQ3dEBNfJR6ibV1m3J4Xdtvd0VFZ6nOytMkmuuGicOAme3bTc1S3ACMt2thUDw/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

![types](https://mmbiz.qpic.cn/mmbiz_png/33P2FdAnjuibCA7zuzhlSIpEHAClQ3dEBAstMWRiciaBWsJECe4ib9XiawJ0KYa6UccNWFp70mxO2agM1DUFYIB3b7Q/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

![domain](https://mmbiz.qpic.cn/mmbiz_png/33P2FdAnjuibCA7zuzhlSIpEHAClQ3dEBw6h6u8RNXzNE3cOVYF7cambLLlIb5ibfcLj9JLynsZL1fPAzsfcdTsA/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

![Application](https://mmbiz.qpic.cn/mmbiz_png/33P2FdAnjuibCA7zuzhlSIpEHAClQ3dEBu1M0GnnGyl9jia9jUhl9SbzQWRTA9X4vw2DWSm91uJBOzliaq9gkM9Rg/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

![infrastructure](https://mmbiz.qpic.cn/mmbiz_png/33P2FdAnjuibCA7zuzhlSIpEHAClQ3dEBicft40OXaibnibT86aj2s11aok4NXVfmcrVI79sVKs5JLtrxa1Dnia06IA/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

![web](https://mmbiz.qpic.cn/mmbiz_png/33P2FdAnjuibCA7zuzhlSIpEHAClQ3dEBCcCumAibDlffTuRD1UiaPyOYaM3VueCDT09UX5ZmYSgQEZayH5Kkb13g/640?wx_fmt=png&wxfrom=5&wx_lazy=1&wx_co=1)

interface[service]
规范：Interface层的HTTP和RPC接口，返回值为Result，捕捉所有异常
规范：一个Interface层的类应该是“小而美”的，应该是面向“一个单一的业务”或“一类同样需求的业务”，需要尽量避免用同一个类承接不同类型业务的需求。
application[Service]

规范：CQE对象的校验应该前置，避免在ApplicationService里做参数的校验。可以通过JSR303/380和Spring Validation来实现
规范：Application层的所有接口返回值为DTO，不负责处理异常
Application层的几个核心类：

ApplicationService应用服务：最核心的类，负责业务流程的编排，但本身不负责任何业务逻辑

DTO Assembler：负责将内部领域模型转化为可对外的DTO

Command、Query、Event对象：作为ApplicationService的入参

返回的DTO：作为ApplicationService的出参


我们可以看出来，ApplicationService的代码通常有类似的结构：AppService通常不做任何决策（Precondition除外），仅仅是把所有决策交给DomainService或Entity，把跟外部交互的交给Infrastructure接口，如Repository或防腐层。

一般的“套路”如下：

准备数据：包括从外部服务或持久化源取出相对应的Entity、VO以及外部服务返回的DTO。

执行操作：包括新对象的创建、赋值，以及调用领域对象的方法对其进行操作。需要注意的是这个时候通常都是纯内存操作，非持久化。

持久化：将操作结果持久化，或操作外部系统产生相应的影响，包括发消息等异步操作。

如果涉及到对多个外部系统（包括自身的DB）都有变更的情况，这个时候通常处在“分布式事务”的场景里，无论是用分布式TX、TCC、还是Saga模式，取决于具体场景的设计，在此处暂时略过。


domain[Service]

单对象（可以把service传入entity，只读，无副作用)
跨领域对象（同时操作多个entity)
