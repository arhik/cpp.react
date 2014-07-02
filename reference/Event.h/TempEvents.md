---
layout: default
title: TempEvents
type_tag: class
---
This class exposes additional type information of the linked node, which enables r-value based node merging at compile time.
`TempEvents` is usually not used as an l-value type, but instead implicitly converted to `Events`.

## Synopsis
{% highlight C++ %}
template
<
    typename D,
    typename E,
    typename TOp
>
class TempEvents : public Events<D,E>
{
public:
    // Constructor
    TempEvents();
    TempEvents(const TempEvents&);
    TempEvents(TempEvents&&);

    // Assignemnt
    TempEvents& operator=(const TempEvents&);
    TempEvents& operator=(TempEvents&& other);
};
{% endhighlight %}


-----

<h1>Constructor <span class="type_tag">member function</span></h1>

Analogously defined to constructor of [Events](#events).