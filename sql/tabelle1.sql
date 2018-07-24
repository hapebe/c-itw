use testdatenbank;

-- create table tabelle1 (spalte1 int, spalte2 varchar(30));
ALTER TABLE tabelle1 DROP uid;

-- show create table tabelle1;
-- show fields from tabelle1;

insert into tabelle1 (spalte1, spalte2) values (1, 'Zeile 1');
insert into tabelle1 (spalte1, spalte2) values (2, 'Zeile 2');
insert into tabelle1 (spalte1, spalte2) values (4.44, 'Zeile 3');
insert into tabelle1 (spalte1, spalte2) values (5, '123456789012345678901234567890');
-- insert into tabelle1 (spalte1) values (222);

update tabelle1 set spalte1=3 where spalte1=4;
update tabelle1 set spalte1=4, spalte2='Zeile 4' where spalte1=5;

ALTER TABLE tabelle1 ADD uid int auto_increment primary key FIRST;

select * from tabelle1;

delete from tabelle1;

-- drop table tabelle1;
-- show tables;
