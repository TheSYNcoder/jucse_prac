
DECLARE 

CURSOR C IS SELECT * FROM EMP ORDER BY BASIC DESC;
BEGIN 

FOR R IN C LOOP
    IF C%ROWCOUNT <= 5 THEN
        DBMS_OUTPUT.PUT_LINE(R.BASIC  || R.EMP_NAME );
    ELSE
        EXIT;
END LOOP;