package ija.ija2020.homework1.store;

import ija.ija2020.homework1.goods.Goods;
import ija.ija2020.homework1.goods.GoodsItem;
import ija.ija2020.homework1.goods.GoodsShelf;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class StoreShelf implements GoodsShelf {
    private Map<Goods, List<GoodsItem>> content = new HashMap();

    public StoreShelf() {
    }
    @Override
    public void put(GoodsItem goodsItem) {
        Goods goods = goodsItem.goods();
        if (this.content.containsKey(goods)) {
            ((List)this.content.get(goods)).add(goodsItem);
        } else {
            List<GoodsItem> lst = new ArrayList();
            lst.add(goodsItem);
            this.content.put(goods, lst);
        }
    }

    @Override
    public boolean containsGoods(Goods goods) {
        List<GoodsItem> lst = (List)this.content.get(goods);
        return lst == null ? false : !lst.isEmpty();
    }

    @Override
    public GoodsItem removeAny(Goods goods) {

        List<GoodsItem> lst = (List)this.content.get(goods);
        if (lst == null) {
            return null;
        } else {
            return lst.isEmpty() ? null : (GoodsItem)lst.remove(0);
        }
    }

    @Override
    public int size(Goods goods) {
        List<GoodsItem> lst = (List)this.content.get(goods);
        return lst == null ? 0 : lst.size();
    }
}
