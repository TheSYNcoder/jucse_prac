
\prompt 'Enter user code here : ' code

create function f123(_code character varying)
    returns void
    language plpgsql
as $$

declare 
    name varchar(255) := 'default';
    cnt integer := 0;

begin
    select emp_name, count(*)
    into name, cnt
    from emp 
    where LOWER(emp_code) = LOWER(_code)
    group by emp_name;


    if cnt > 0 then
        raise notice 'The name of the given code: % is %' , 
        _code, name;
    else 
        raise exception 'Employee not found with code : %' , _code
            using hint = 'Check the code again!';
    end if;

end; 
$$;

select f123(:'code');

drop function f123(varchar);


    

