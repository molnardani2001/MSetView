#ifndef MSETSVIEW_H
#define MSETSVIEW_H

#include <set>
#include <functional>
#include <algorithm>

template<class T, class P, class Comp1 = std::less<T>, class Comp2 = std::less<T>>
class multisets_predicate_view
{
    
    std::multiset<T, Comp1> set_a;
    std::multiset<T, Comp2> set_b;
    std::multiset<T, Comp1> *addr_a;
    std::multiset<T, Comp2> *addr_b;
    P predicate;

    void init(std::multiset<T,Comp1>& a, std::multiset<T,Comp2>& b){
        addr_a = &a;
        addr_b = &b;

        a.clear();
        b.clear();

        typedef typename std::multiset<T>::iterator it;
        for(it iter = set_a.begin(); iter != set_a.end(); iter++){
            if(predicate(*iter)){
                a.insert(*iter);
            }else{
                b.insert(*iter);
            }
        }

        for(it iter = set_b.begin(); iter != set_b.end(); iter++){
            if(predicate(*iter)){
                a.insert(*iter);
            }else{
                b.insert(*iter);
            }
        }
    }

public:
    multisets_predicate_view(std::multiset<T, Comp1>& a, std::multiset<T, Comp2>& b, P predicate) :set_a(a), set_b(b), predicate(predicate)
    {
        init(a,b);
    }

    multisets_predicate_view(std::multiset<T, Comp1>& a, std::multiset<T, Comp2>& b) : set_a(a), set_b(b)
    {
        init(a,b);
    }

    int size() const{
        return set_a.size() + set_b.size();
    }

    int count(const T& value) const {
        return set_a.count(value) + set_b.count(value); 
    }

    ~multisets_predicate_view()
    {
        // typedef typename std::multiset<T>::iterator it;

        *addr_a = std::multiset<T,Comp1>(set_a.begin(), set_a.end());
        *addr_b = std::multiset<T,Comp2>(set_b.begin(), set_b.end());
    }

};

#endif /* MSETSVIEW_H */