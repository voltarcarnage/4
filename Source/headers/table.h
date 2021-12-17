#include <iostream>
#include <cstring>

#pragma once

namespace Game_N{

  /*!
   * @brief Структура элемента таблицы
   * @tparam IND - ключ
   * @tparam INF - значение
  */

  template <class IND, class INF>
  struct Pair{
    IND first;
    INF second;
  /*!
   * @brief Стандартный конструктор структуры пары
   *
  */
    Pair():first(IND()), second(0){}
  /*!
   * @brief Стандартный конструктор структуры пары
   * @param name - параметр ключ
  */
    Pair(const IND& name):first(name), second(0){}
  };

  /*!
   * @brief Класс итератор для таблицы
   * @tparam IND - параметр ключ
   * @tparam INF - параметр значение
  */

  template <class IND, class INF>
  class TableIt{
    private:
      Pair<IND,INF> *cur;///Элемент
    public:
      /*!
       * @brief Стандартный конструктор класса итератора
      */
      TableIt():cur(0){}
      /*!
       * @brief Конструктор класса итератора
       * @param a - Элемент таблицы
      */
      TableIt(Pair<IND,INF> *a):cur(a){}
      /*!
       * @brief Перегруженный оператор неравенства для итератора
       * @param Константная ссылка на таблицу
       * @return Возвращает 1 или 0
      */
      int operator !=(const TableIt<IND, INF> &) const;
      /*!
       * @brief Перегруженный оператор сравнения равенства для итератора
       * @param Константная ссылка на таблицу
       * @return Функция возвращает 1 или 0
      */
      int operator ==(const TableIt<IND, INF> &) const;
      /*!
       * @brief Перегруженный оператор разыменования
       * @return Возвращает ссылку на элемент таблицы
      */
      Pair<IND, INF>& operator *();
      /*!
       * @brief Перегруженный оператор доступа по указателю
       * @return Возвращает указатель на элемент таблицы
      */
      Pair<IND, INF>* operator ->();
      /*!
       * @brief Перегруженный оператор префиксного инкремента для хождения по таблице
       * @return Возвращает ссылку на таблицу
      */
      TableIt<IND, INF>& operator ++();
      /*!
       * @brief Перегруженный оператор постфиксного инкремента для хождения по таблице
       * @param Пустой int для перегрузки постфиксного инкремента
       * @return Возвращает таблицу
      */
      TableIt<IND, INF> operator ++(int);
  };

  /*!
   * @brief Класс таблицы
   * @tparam IND - параметр ключ
   * @tparam INF - параметр значение
  */
  template <class IND, class INF>
  class Table{
      friend class TableIt<IND, INF>;///Класс итератор
    private:
      static const int QUOTA = 10;///Квота
      int cnt, cur;///Макс кол-во элементов и кол-во текущих элементов
      Pair<IND,INF> *arr;///Массив пар
      /*!
       * @brief Метод возвращающий индекс элемента по ключу
       * @param Константная ссылка на ключ
       * @return Возвращает индекс элемента, если найден, иначе -1
      */
      int getPos(const IND &) const;

    public:
      /*!
       * @brief Стандартный конструктор таблицы
      */
      Table():cnt(QUOTA), cur(0),arr(new Pair<IND, INF>[QUOTA]){}
      /*!
       * @brief Копирующий конструктор таблицы
       * @param  Константная ссылка на таблицу
      */
      Table(const Table<IND, INF> &);
      /*!
       * @brief Деструктор таблицы
      */
      ~Table(){delete []arr;}
      /*!
       * @brief Перегруженный оператор присваивания(копирующий)
       * @param Константная ссылка на таблицу
       * @return Возвращает ссылку на таблицу
      */
      Table<IND, INF>& operator =(const Table<IND, INF> &);
      /*!
       * @brief Метод изменения информации по индексу
       * @param Константная ссылка на индекс и на информацию
      */
      void setInf(const IND &, const INF &);
      /*!
       * @brief Метод добавления заклинания в таблицу
       * @param Константная ссылка на индекс и на информацию
      */
      void addSpell(const IND &,const INF &);
      /*!
       * @brief Метод получения размеров таблицы
       * @return Возвращает размер таблицы
      */
      int getSize();
      /*!
       * @brief Перегруженный оператор индексации l-value
       * @param Константная ссылка на индекс
       * @return Возвращает ссылку на поле информации по данному индексу
      */
      INF & operator[](const IND &); // l-value
      /*!
       * @brief Перегруженный оператор индексации r-value
       * @param Константная ссылка на индекс
       * @return Возвращает константную ссылку на поле информации по данному индексу
      */
      const INF & operator[](const IND &) const; // r-value
      typedef TableIt<IND, INF> Iterator;
      /*!
       * @brief Метод начальный элемент таблицы
       * @return Возвращает итератор на начало таблицы
      */
      Iterator begin( );
      /*!
       * @brief Метод конечный элемент таблицы
       * @return Возвращает итератор на конец таблицы
      */
      Iterator end( );
      /*!
       * @brief Метод поиска в таблице по индексу
       * @param Константная ссылка на поле индекса
       * @return Возвращает итератор на элемент с таким индексом
      */
      Iterator find(const IND &) const;
  };

  template <class IND, class INF>
  void Table<IND,INF>::setInf(const IND & ind, const INF &inf)
  {
    for(int i = 0; i < cur; ++i)
      if(arr[i].first == ind)
        arr[i].second = inf;
  }

  template <class IND, class INF>
  int Table<IND,INF>::getSize()
  {
    return cur;
  }

  template <class IND, class INF>
  void Table<IND,INF>::addSpell(const IND & ind, const INF &inf)
  {
    Pair<IND,INF> * arrTemp = new Pair<IND,INF>[cur + 1];
    for(int i = 0; i < cur; i++)
    {
      arrTemp[i].first = arr[i].first;
      arrTemp[i].second = arr[i].second;
    }
    arrTemp[cur].first = ind;
    arrTemp[cur].second = inf;

    arr = arrTemp;

    cur++;
  }

  template <class IND, class INF>
  Table<IND, INF>::Table(const Table<IND, INF> &a):cnt(a.cnt), cur(a.cur), arr(new Pair<IND,INF>[a.cnt])
  {
    for(int i = 0; i < cur; ++i)
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
      throw ("Illegal index");
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
