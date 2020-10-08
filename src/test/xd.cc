/***********************************************/
struct NIL {
  typedef NIL head;
  typedef NIL tail;
};

template <class H, class T=NIL> struct Lst {
  typedef H head;
  typedef T tail;
};
/***********************************************/

/***********************************************/
template <class X, class Y> struct Eq { static const bool result = false; };
template <class X> struct Eq<X, X> { static const bool result = true; };
/***********************************************/

/***********************************************/
template <class Elm, class LST> struct Position {
private:
  typedef typename LST::head H;
  typedef typename LST::tail T;
  static const bool found = Eq<H, Elm>::result;
public:
  static const int result = found? 1 : 1 + Position<Elm, T>::result;
};

template <class Elm> struct Position<Elm, NIL> {
  static const int result = 0;
};
/***********************************************/


/***********************************************/
template <typename LST, int N> struct Nth {
  typedef typename LST::Tail Tail;
  typedef typename Nth<Tail, N-1>::result result;
};

template <typename LST> struct Nth<LST, 0> {
  typedef typename LST::head result;
};
/***********************************************/


/***********************************************/
template <typename Lst> struct Instances {
  typedef typename Lst::head Elm;
  Elm instance;
  Instances<Lst::tail> next;
};
template <> struct Instances<NIL> {};
/***********************************************/


/***********************************************/
template <int N, typename TypeLst> struct NthInstance {
  // This one isnt easy...

  // This is the next type in the list
  typedef typename TypeLst::tail TypeNext;

  //  * Nth::result is the Nth type in Lst (i.e. char, int, ...)
  typedef typename NthInstance<N-1, TypeLst>::NthInstanceType NthInstanceType;

  //  * typename Nth::result & is a reference to said type and the ret type
  template <InstancesLst>
  static NthInstanceType& get(InstancesLst &instances_lst) {
    return NthInstance::get(instances_lst.next);
  }
};

// Remember, just for fun we choose a 1-based system (wtf..)
template <typename TypeLst> struct NthInstance<1, TypeLst> {
  typedef typename TypeLst::head NthInstanceType;

  template <InstancesLst>
  static NthInstanceType& get(InstancesLst &instances_lst) {
    return instances_lst.instance;
  }
};
/***********************************************/


class Facade {
  typedef Lst<int, Lst<char, Lst > > Lst;
  Instances<Lst> instances;

public:
  template <typename PK> int find(PK) {
    return Position<PK, Lst>::result;
  }

  template <typename PK>
  // This is a difficult one... it should be parsed like this:
  //  1) Get the desired instance position using Position::result
  //  2) Get the type @ the desired position with NthInstance::Type
  //  3) Define said type as a return type (with an & at the end, i.e. make
  //      it a reference to the return type)
  typename NthInstance< Lst, Position::result >::NthInstanceType&
  get_instance(PK) {
    const int idx_position = Position<PK, Lst>::result;
    typedef typename NthInstance<idx_position>::NthInstanceType IdxType;
    IdxType &idx = NthInstance<idx_position>::get( instances );
    return idx;
  }
};

#include <iostream>

int main() {
  Facade f;
  int &a = f.get_instance(1);
  char &b = f.get_instance('a');
  float &c = f.get_instance(1.0);
  a = 42; b = 'n'; c = 4.2;
  std::cout << f.get_instance(1) << "\n";
  std::cout << f.get_instance('a') << "\n";
  std::cout << f.get_instance(1.0) << "\n";
  a = 43; b = 'm'; c = 5.2;
  std::cout << f.get_instance(1) << "\n";
  std::cout << f.get_instance('a') << "\n";
  std::cout << f.get_instance(1.0) << "\n";
  return 0;
}