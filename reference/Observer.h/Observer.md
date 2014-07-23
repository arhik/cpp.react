---
layout: default
title: Observer
type_tag: class
groups: 
 - {name: Home, url: ''}
 - {name: Reference , url: 'reference/'}
 - {name: Observer.h, url: 'reference/Observer.h/'}
---
An instance of this class provides a unique handle to an observer which can be used to detach it explicitly.
It also holds a strong reference to the observed subject, so while it exists the subject and therefore the observer will not be destroyed.

If the handle is destroyed without calling `Detach()`, the lifetime of the observer is tied to the subject.

## Synopsis
{% highlight C++ %}
template <typename D>
class Observer
{
public:
    // Constructor
    Observer();
    Observer(Observer&& other);

    // Assignemnt
    Observer& operator=(Observer&& other)

    bool IsValid() const;

    void Detach();
};
{% endhighlight %}