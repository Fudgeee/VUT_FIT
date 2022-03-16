package ija.ija2020.homework1.store;

import ija.ija2020.homework1.goods.Goods;
import ija.ija2020.homework1.goods.GoodsItem;

import java.time.LocalDate;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

public class StoreGoods implements Goods {
    private String name;

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        StoreGoods that = (StoreGoods) o;
        return Objects.equals(name, that.name);
    }

    @Override
    public int hashCode() {
        return Objects.hash(name);
    }

    public StoreGoods(String name) {
        this.name = name;
    }
    @Override
    public String getName() {
        return name;
    }

    private List<GoodsItem> goods = new ArrayList();
    @Override
    public boolean addItem(GoodsItem goodsItem) {
        return this.goods.add(goodsItem);
    }

    @Override
    public GoodsItem newItem(LocalDate localDate) {
        GoodsItem newItem = new StoreGoodsItem(this, localDate);
        this.goods.add(newItem);
        return newItem;
    }

    @Override
    public boolean remove(GoodsItem goodsItem) {
        if (goodsItem == null){
            return false;
        }
        else{
            return this.goods.remove(goodsItem);
        }
    }

    @Override
    public boolean empty() {
        return this.goods.size() == 0;
    }

    @Override
    public int size() {
        return this.goods.size();
    }
}
