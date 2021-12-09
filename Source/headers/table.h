#include <exception>

namespace Game_N{

  template <class IND, class INF>
  struct Pair{
    IND first;
    INF second;
    Pair():first(IND()), second(0){}
    Pair(const IND& name):first(name), second(0){}
  };

  template <class IND, class INF>
  class TableIt;

  template <class IND, class INF>
  class Table{
      friend class TableIt<IND, INF>;
    private:
      static const int QUOTA = 10;
      int cnt, cur;
      Pair<IND,INF> *arr;
      int getPos(const IND &) const;

    public:
      Table():cnt(QUOTA), cur(0),arr(new Pair<IND, INF>[QUOTA]){}
      Table(const Table<IND, INF> &);
      ~Table(){delete []arr;}

      Table<IND, INF>& operator =(const Table<IND, INF> &);

      INF & operator[](const IND &); // l-value
      const INF & operator[](const IND &) const; // r-value
      typedef TableIt<IND, INF> Iterator;
      Iterator begin( );
      Iterator end( );
      Iterator find(const IND &) const;
  };

  template <class IND, class INF>
  Table<IND, INF>::Table(const Table<IND, INF> &a):cnt(a.cnt), cur(a.cur), arr(new Pair<IND,INF>[a.cnt])
  {
    for(int i = 0; i < cnt; ++i)
      arr[i] = a.arr[i];
  }

  template <class IND, class INF>
  Table<IND, INF>& Table<IND, INF>::operator = (const Table<IND, INF> &a)
  {
    if(this != &a) {
      delete [ ] arr;
      arr = new Pair<IND, INF> [cnt = a.cnt];
      cur = a.cur;
      for(int i = 0; i < cnt; ++i)
        arr[i] = a.arr[i];
    }
    return *this;
  }

  template <class IND, class INF>
  int Table<IND,INF>::getPos(const IND &s) const
  {
    for(int i = 0; i < cur; ++i)
      if(arr[i].first == s)
        return i;

    return -1;
  }

  template <class IND, class INF>
  INF& Table<IND,INF>::operator [](const IND &s)
  {
    int i = getPos(s);
    if(i < 0)
    {
      i = cur;
      if(cur >= cnt)
      {
        Pair<IND,INF> *old = arr;
        arr = new Pair<IND,INF>[cnt += QUOTA];
        for(i = 0; i < cur; i++){
          arr[i] = old[i];
        }

        delete []old;
      }
      arr[cur].first = s;
      ++cur;
    }
    return arr[i].second;
  }

  template <class IND, class INF>
  const INF & Table<IND, INF>::operator[](const IND &s) const
  {
    int i = getPos(s);
    if (i < 0)
      throw std::exception("Illegal index");
    return arr[i].second;
  }

  template <class IND, class INF>
  TableIt<IND, INF> Table<IND, INF>::begin()
  {
    return TableIt<IND, INF>(this->arr);
  }

  template <class IND, class INF>
  TableIt<IND, INF> Table<IND, INF>::end()
  {
    return TableIt<IND, INF>(this->arr + cur);
  }

  template <class IND, class INF>
  TableIt<IND, INF> Table<IND, INF>::find(const IND &s) const
  {
    int i = getPos(s);
    if(i < 0)
      i = cur;
    return TableIt<IND, INF>(this->arr + i);
  }

  template <class IND, class INF>
  class TableIt{
    private:
      Pair<IND,INF> *cur;
    public:
      TableIt():cur(0){}
      TableIt(Pair<IND,INF> *a):cur(a){}
      int operator !=(const TableIt<IND, INF> &) const;
      int operator ==(const TableIt<IND, INF> &) const;
      Pair<IND, INF>& operator *();
      Pair<IND, INF>* operator ->();
      TableIt<IND, INF>& operator ++();
      TableIt<IND, INF> operator ++(int);
  };

  template <class IND, class INF>
  int TableIt<IND, INF>::operator !=(const TableIt<IND, INF> &it) const
  {
    return cur != it.cur;
  }

  template <class IND, class INF>
  int TableIt<IND, INF>::operator ==(const TableIt<IND, INF> &it) const
  {
    return cur == it.cur;
  }

  template <class IND, class INF>
  Pair<IND, INF>& TableIt<IND, INF>::operator *( )
  {
    return *cur;
  }

  template <class IND, class INF>
  Pair<IND, INF>* TableIt<IND, INF>::operator ->( )
  {
    return cur;
  }

  template <class IND, class INF>
  TableIt<IND, INF>& TableIt<IND, INF>::operator ++( )
  {
    ++cur;
    return *this;
  }

  template <class IND, class INF>
  TableIt<IND, INF> TableIt<IND, INF>::operator ++(int)
  {
    TableIt<IND, INF> res(*this);
    ++cur;
    return res;
  }


}
