
create function f123()
    returns void
    language plpgsql
as $$

declare

    f record;

begin

    for f in select * from emp e, leave l, months m 
        where l.emp_code = e.emp_code and m.month = l.month 
    loop
        raise notice 'Employee % - % : Calculated Basic : %', f.emp_code, f.emp_name, 
        f.basic - (f.basic * f.no_of_days)/f.days;

    end loop;


end; 
$$;

select f123();

drop function f123();


    

