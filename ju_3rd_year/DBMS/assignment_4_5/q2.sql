
\prompt 'Enter user code here : ' code
\prompt 'Enter employee name :' name
\prompt 'Enter department code : ' dept_code
\prompt 'Enter designation code : ' desig_code
\prompt 'Enter sex: ' sex
\prompt 'Enter address : ' address
\prompt 'Enter city : ' city
\prompt 'Enter state : ' state
\prompt 'Enter pin : ' pin
\prompt 'Enter basic: ' basic
\prompt 'Enter joining date : ' jn_dt



create function f123(_code varchar, _name varchar, _dept_code varchar, _desig_code varchar,
_sex varchar, _address varchar, _city varchar, _state varchar, _pin varchar,
_basic integer, _jn_dt date)
    returns void
    language plpgsql
as $$

declare 
    cnt integer := 0;

begin
    select count(*)
    into cnt
    from emp 
    where LOWER(emp_code) = LOWER(_code);


    if cnt > 0 then
        raise notice 'The given code %  exists please enter new code', _code
    end if;

    insert into emp values( _code, _name, _dept_code, 
        _desig_code, _sex, _address, _city, _state, _pin, _basic, _jn_dt );
    
end; 
$$;

select f123(:'code', :'name' , :'dept_code' , :'desig_code', :'sex', :'address', :'city', :'state' , :'pin', basic, :'jn_dt');

drop function f123(varchar, varchar,varchar, varchar, varchar, varchar, varchar, varchar, varchar, integer, date );


    

