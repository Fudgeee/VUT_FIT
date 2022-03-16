package ija.ija2020.homework1.store;

import ija.ija2020.homework1.goods.Goods;
import ija.ija2020.homework1.goods.GoodsItem;

import java.time.LocalDate;

public class StoreGoodsItem implements GoodsItem {
    private final LocalDate localDate;

    public StoreGoodsItem(Goods goods, LocalDate localDate) {
        this.goods = goods;
        this.localDate = localDate;
    }
    private Goods goods;
    @Override
    public Goods goods() {
        return this.goods;
    }

    @Override
    public boolean sell() {
        return this.goods.remove(this);
    }
}
