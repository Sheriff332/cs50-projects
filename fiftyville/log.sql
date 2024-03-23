-- Keep a log of any SQL queries you execute as you solve the mystery.
.tables
.schema
SELECT * FROM crime_scene_reports WHERE year=2023 AND month = 7 AND day = 28 AND street= 'Humphrey Street';
SELECT * FROM bakery_security_logs WHERE month = 7 AND day = 28 AND hour = 10;
SELECT * FROM interviews WHERE year=2023 AND month = 7 AND day = 28;
SELECT name,license_plate FROM people WHERE license_plate in ('5P2BI95', '94KL13X','6P58WS2','4328GD8','G412CB7','L93JTIZ','322W7JE','0NTHK55','1106N58');
SELECT * FROM atm_transactions WHERE month = 7 AND day = 28 AND atm_location = 'Leggett Street';
SELECT people.name,bank_accounts.account_number FROM people JOIN bank_accounts ON people.id = bank_accounts.person_id WHERE bank_accounts.account_number IN (28500762,28296815,76054385,49610011,16153065,25506511,81061156,26013199);
SELECT name,phone_number FROM people WHERE name in ('Iman','Taylor','Luca','Diana','Bruce');
SELECT caller, receiver, duration FROM phone_calls WHERE month=7 AND day=28 AND caller IN ('(829) 555-5269','(286) 555-6063','(389) 555-5198','(770) 555-1861','(367) 555-5533');
SELECT * FROM flights WHERE month = 7 AND day = 29 AND origin_airport_id=8;
SELECT name FROM people JOIN passengers ON passengers.passport_number = people.passport_number WHERE passengers.flight_id = 36;
SELECT city  FROM airports WHERE id = 4;
