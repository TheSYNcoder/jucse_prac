


create function f123()
    returns table(basic integer, emp_name varchar)
    language plpgsql
as $$

begin
    return query select distinct on (rnk.basic) rnk.basic, rnk.emp_name from 
    ( select * , rank() over ( order by emp.basic desc) from emp) rnk 
    where rank < 6 order by basic desc;

end; 
$$;

select * from f123();

drop function f123();


    

