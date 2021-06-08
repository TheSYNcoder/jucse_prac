
create table ORDERMAST ( ORDER_NO varchar(5) PRIMARY KEY , ORDER_DT DATE );
create table ORDERDETAILS ( ORDER_NO varchar(5) , ITEM_NO VARCHAR(5) , QTY INTEGER, CONSTRAINT ORDER_ITEM PRIMARY KEY(ORDER_NO, ITEM_NO) );
create table DELIVERYMAST ( DELV_NO varchar(5) PRIMARY KEY , ORDER_NO VARCHAR(5), DELV_DT DATE );
create table DELIVERYDETAILS ( DELV_NO varchar(5) , ITEM_NO VARCHAR(5), QTY INTEGER, CONSTRAINT DELV_ITEM PRIMARY KEY(DELV_NO, ITEM_NO) );


INSERT INTO ORDERMAST VALUES('OD1' , '2021-01-28');
INSERT INTO ORDERMAST VALUES('OD2' , '2021-02-28');
INSERT INTO ORDERMAST VALUES('OD3' , '2021-01-25');
INSERT INTO ORDERMAST VALUES('OD4' , '2021-01-26');
INSERT INTO ORDERMAST VALUES('OD5' , '2021-01-27');


INSERT INTO ORDERDETAILS VALUES( 'OD3' , 'IT1' , 4 );
INSERT INTO ORDERDETAILS VALUES( 'OD3' , 'IT2' , 3 );
INSERT INTO ORDERDETAILS VALUES( 'OD3' , 'IT5' , 4 );
INSERT INTO ORDERDETAILS VALUES( 'OD3' , 'IT3' , 1 );
INSERT INTO ORDERDETAILS VALUES( 'OD4' , 'IT1' , 2 );
INSERT INTO ORDERDETAILS VALUES( 'OD4' , 'IT3' , 4 );
INSERT INTO ORDERDETAILS VALUES( 'OD2' , 'IT2' , 5 );
INSERT INTO ORDERDETAILS VALUES( 'OD2' , 'IT1' , 1 );
INSERT INTO ORDERDETAILS VALUES( 'OD5' , 'IT1' , 4 );
INSERT INTO ORDERDETAILS VALUES( 'OD5' , 'IT5' , 2 );
INSERT INTO ORDERDETAILS VALUES( 'OD5' , 'IT4' , 4 );
INSERT INTO ORDERDETAILS VALUES( 'OD1' , 'IT1' , 2 );
INSERT INTO ORDERDETAILS VALUES( 'OD1' , 'IT3' , 4 );


INSERT INTO DELIVERYMAST VALUES( 'DEL1', 'OD1' , '2021-02-03' );
INSERT INTO DELIVERYMAST VALUES( 'DEL2', 'OD1' , '2021-02-05' );
INSERT INTO DELIVERYMAST VALUES( 'DEL3', 'OD1' , '2021-02-07' );
INSERT INTO DELIVERYMAST VALUES( 'DEL4', 'OD5' , '2021-02-01' );
INSERT INTO DELIVERYMAST VALUES( 'DEL5', 'OD5' , '2021-02-10' );
INSERT INTO DELIVERYMAST VALUES( 'DEL6', 'OD2' , '2021-02-12' );
INSERT INTO DELIVERYMAST VALUES( 'DEL7', 'OD4' , '2021-02-15' );
INSERT INTO DELIVERYMAST VALUES( 'DEL8', 'OD3' , '2021-02-04' );
INSERT INTO DELIVERYMAST VALUES( 'DEL9', 'OD3' , '2021-02-10' );

INSERT INTO DELIVERYDETAILS VALUES( 'DEL1', 'IT1' , 1 );
INSERT INTO DELIVERYDETAILS VALUES( 'DEL1', 'IT3' , 2 );
INSERT INTO DELIVERYDETAILS VALUES( 'DEL2', 'IT3' , 1 );
INSERT INTO DELIVERYDETAILS VALUES( 'DEL2', 'IT1' , 1 );
INSERT INTO DELIVERYDETAILS VALUES( 'DEL3', 'IT3' , 1 );
INSERT INTO DELIVERYDETAILS VALUES( 'DEL4', 'IT5' , 2 );
INSERT INTO DELIVERYDETAILS VALUES( 'DEL4', 'IT1' , 2 );
INSERT INTO DELIVERYDETAILS VALUES( 'DEL5', 'IT1' , 2 );
INSERT INTO DELIVERYDETAILS VALUES( 'DEL6', 'IT2' , 5 );
INSERT INTO DELIVERYDETAILS VALUES( 'DEL6', 'IT1' , 1 );
INSERT INTO DELIVERYDETAILS VALUES( 'DEL7', 'IT1' , 2 );
INSERT INTO DELIVERYDETAILS VALUES( 'DEL7', 'IT3' , 4 );
INSERT INTO DELIVERYDETAILS VALUES( 'DEL8', 'IT1' , 4 );
INSERT INTO DELIVERYDETAILS VALUES( 'DEL8', 'IT2' , 3 );
INSERT INTO DELIVERYDETAILS VALUES( 'DEL9', 'IT5' , 4 );
INSERT INTO DELIVERYDETAILS VALUES( 'DEL9', 'IT3' , 1 );





