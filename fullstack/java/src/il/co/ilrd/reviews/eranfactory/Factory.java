package il.co.ilrd.reviews.eranfactory;

import java.util.Map;
import java.util.HashMap;
import java.util.function.Function;

public class Factory<K,T, D> {
    Map<K, Function< D, ? extends T>> map;

    public Factory(){
        map = new HashMap<>();
    }

    //Function gets D data and return T type.
    //Function gets added to the hashMap at given key
    public Function<D, ? extends T> add (K key, Function<D, ? extends T> func){
        return  map.put(key, func);
    }

    //the function associated with key is called and given data of type D (as required)
    public T create(K key, D data){
        return map.get(key).apply(data);
    }
}
