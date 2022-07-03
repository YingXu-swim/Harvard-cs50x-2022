-- Keep a log of any SQL queries you execute as you solve the mystery.

-- step 1: find correspond description
-- return:
-- Theft of the CS50 duck took place at 10:15am at the Humphrey Street bakery. Interviews were conducted today with three witnesses who were present at the time – each of their interview transcripts mentions the bakery.
-- Littering took place at 16:36. No known witnesses.
-- key: 10:15am, Humphrey Street bakery, three witnesses,
select * from crime_scene_reports where year = 2021 and month = 7 and day = 28 and street like '%Humphrey Street%';

-- step 2: find intervie
-- we can see id is 159 - 163, 191.
-- 3 witnesses's interview report should be continuously. According to the content, we can infer that 161-163 is the correspond intervie.
-- key:
-- Ruth : bakery parking(within ten minutes of the theft);
-- Eugene: recognized, thief in ATM(Leggett Street, Earlier this morning);
-- Raymond: CALL(less than a minute, As the thief was leaving the bakery), earliest flight out of Fiftyville tomorrow(booked by accomplice).
select * from interviews where year = 2021 and month = 7 and day = 28;

-- step 3: analyse interviews

-- analyse Ruth's interview
-- get license_plate from related bakery parking information
-- track id and name according to license_plate
-- consider this as list1
select id from people where license_plate in (select license_plate from bakery_security_logs where year = 2021 and month = 7 and day = 28 and hour = 10 and minute >= 15 and minute <= 25 and activity = 'exit');

-- analyse Eugene's interview
-- analyse related ATM records, we can also find Taylor's information. Once again revealing that he is the thift.
-- consider this as list2
select person_id from bank_accounts where account_number in (select account_number from atm_transactions where year = 2021 and month = 7 and day = 28 and atm_location like '%Leggett Street%' and transaction_type = 'withdraw');

-- analyse Raymond's interview
-- consider this as list3
select id from people where phone_number in (select caller from phone_calls where year = 2021 and month = 7 and day = 28 and duration < 60);

-- so, we can know: thift's id in list1,2,3
select id from people where id in (select id from people where license_plate in (select license_plate from bakery_security_logs where year = 2021 and month = 7 and day = 28 and hour = 10 and minute >= 15 and minute <= 25 and activity = 'exit')) and id in (select person_id from bank_accounts where account_number in (select account_number from atm_transactions where year = 2021 and month = 7 and day = 28 and atm_location like '%Leggett Street%' and transaction_type = 'withdraw')) and id in (select id from people where phone_number in (select caller from phone_calls where year = 2021 and month = 7 and day = 28 and duration < 60));
-- so, there are 2 candidates (THIEF)

-- suspected phone call records
select receiver from phone_calls where year = 2021 and month = 7 and day = 28 and duration < 60 and caller in (select phone_number from people where id in (select id from people where license_plate in (select license_plate from bakery_security_logs where year = 2021 and month = 7 and day = 28 and hour = 10 and minute >= 15 and minute <= 25 and activity = 'exit')) and id in (select person_id from bank_accounts where account_number in (select account_number from atm_transactions where year = 2021 and month = 7 and day = 28 and atm_location like '%Leggett Street%' and transaction_type = 'withdraw')) and id in (select id from people where phone_number in (select caller from phone_calls where year = 2021 and month = 7 and day = 28 and duration < 60)));
select * from people where phone_number in (select receiver from phone_calls where year = 2021 and month = 7 and day = 28 and duration < 60 and caller in (select phone_number from people where id in (select id from people where license_plate in (select license_plate from bakery_security_logs where year = 2021 and month = 7 and day = 28 and hour = 10 and minute >= 15 and minute <= 25 and activity = 'exit')) and id in (select person_id from bank_accounts where account_number in (select account_number from atm_transactions where year = 2021 and month = 7 and day = 28 and atm_location like '%Leggett Street%' and transaction_type = 'withdraw')) and id in (select id from people where phone_number in (select caller from phone_calls where year = 2021 and month = 7 and day = 28 and duration < 60))));
-- so, there are 2 candidates (ACCOMPLICE)

-- earliest flight out of Fiftyville next day
select id from flights where year = 2021 and month = 7 and day = 29 order by hour asc;
-- so, flight id is 36

select city from airports where id = (select destination_airport_id from flights where  year = 2021 and month = 7 and day = 29 and id = 36);
-- so, we can know: destination is New York City

-- search passengers info
select passport_number from passengers where flight_id = 36 and passport_number in (select passport_number from people where id in (select id from people where license_plate in (select license_plate from bakery_security_logs where year = 2021 and month = 7 and day = 28 and hour = 10 and minute >= 15 and minute <= 25 and activity = 'exit')) and id in (select person_id from bank_accounts where account_number in (select account_number from atm_transactions where year = 2021 and month = 7 and day = 28 and atm_location like '%Leggett Street%' and transaction_type = 'withdraw')) and id in (select id from people where phone_number in (select caller from phone_calls where year = 2021 and month = 7 and day = 28 and duration < 60)));

select id, name from people where passport_number in (select passport_number from passengers where flight_id = 36 and passport_number in (select passport_number from people where id in (select id from people where license_plate in (select license_plate from bakery_security_logs where year = 2021 and month = 7 and day = 28 and hour = 10 and minute >= 15 and minute <= 25 and activity = 'exit')) and id in (select person_id from bank_accounts where account_number in (select account_number from atm_transactions where year = 2021 and month = 7 and day = 28 and atm_location like '%Leggett Street%' and transaction_type = 'withdraw')) and id in (select id from people where phone_number in (select caller from phone_calls where year = 2021 and month = 7 and day = 28 and duration < 60))));
-- only 1 record, so we can know: Bruce is THIEF, id is 686048;

-- get ACCOMPLICE according to call records
select id, name from people where phone_number in (select receiver from phone_calls where year = 2021 and month = 7 and day = 28 and duration < 60 and caller = (select phone_number from people where passport_number in (select passport_number from passengers where flight_id = 36 and passport_number in (select passport_number from people where id in (select id from people where license_plate in (select license_plate from bakery_security_logs where year = 2021 and month = 7 and day = 28 and hour = 10 and minute >= 15 and minute <= 25 and activity = 'exit')) and id in (select person_id from bank_accounts where account_number in (select account_number from atm_transactions where year = 2021 and month = 7 and day = 28 and atm_location like '%Leggett Street%' and transaction_type = 'withdraw')) and id in (select id from people where phone_number in (select caller from phone_calls where year = 2021 and month = 7 and day = 28 and duration < 60))))));
