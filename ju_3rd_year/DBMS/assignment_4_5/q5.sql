
\prompt 'Enter start date : ' st_dt
\prompt 'Enter end date : ' end_dt

create function f123(_st date, _end date)
    returns table( delv_no varchar, order_no varchar, delv_dt date, item_no varchar, qty integer, order_dt date )
    language plpgsql
as $$

begin
    return query
    select dm.delv_no, dm.order_no, dm.delv_dt,
    dd.item_no, dd.qty, ood.order_dt
    from deliverymast dm, deliverydetails dd,orderdetails od, 
    ( select * from ordermast om where om.order_dt between _st and _end ) ood 
    where dm.delv_no = dd.delv_no and ood.order_no = od.order_no;

end; 
$$;

select * from f123(:'st_dt', :'end_dt');

drop function f123(date, date);


    

