-- Создание таблицы gift
CREATE TABLE IF NOT EXISTS gift (
    sender_id INT NOT NULL,
    receiver_id INT NOT NULL,
    cost INT NOT NULL,
    time TIMESTAMP NOT NULL,
    PRIMARY KEY (sender_id, receiver_id, time)
);

-- Создание таблицы request_friend
CREATE TABLE IF NOT EXISTS request_friend (
    sender_id INT NOT NULL,
    receiver_id INT NOT NULL,
    time_approved TIMESTAMP,
    PRIMARY KEY (sender_id, receiver_id)
);

--INSERT INTO gift (sender_id, receiver_id, cost, time) VALUES
--(2, 1, 500, '2025-09-01 10:01:00');
--(1, 2, 1500, '2025-09-01 10:00:00');
--(1, 2, 200, '2025-09-01 10:01:00');
--(2, 3, 1500, '2025-09-02 11:00:00'),
--(3, 4, 800, '2025-09-03 12:00:00'),
--(4, 5, 2000, '2025-09-04 13:00:00'),
--(5, 1, 1200, '2025-09-05 14:00:00'),
--(1, 3, 900, '2025-09-06 15:00:00'),
--(2, 4, 1100, '2025-09-07 16:00:00'),
--(3, 5, 700, '2025-09-08 17:00:00'),
--(4, 1, 1800, '2025-09-09 18:00:00'),
--(5, 2, 1300, '2025-09-10 19:00:00');


--INSERT INTO request_friend (sender_id, receiver_id, time_approved) VALUES
--(1, 2, '2025-09-02 00:00:00'),
--(2, 3, '2025-09-03 00:00:00'),
--(3, 4, '2025-09-04 00:00:00'),
--(4, 5, '2025-09-05 00:00:00'),
--(5, 1, '2025-09-06 00:00:00'),
--(1, 3, NULL),
--(2, 4, '2025-09-08 00:00:00'),
--(3, 5, '2025-09-09 00:00:00'),
--(4, 1, '2025-09-10 00:00:00'),
--(5, 2, '2025-09-11 00:00:00');
--(2, 1, '2025-09-20 00:00:00'),
--(3, 2, '2025-09-02 11:00:00');

SELECT 
    COUNT(*) / 2 as pairs
FROM gift g
JOIN request_friend rf1 ON g.sender_id = rf1.sender_id AND g.receiver_id = rf1.receiver_id
JOIN request_friend rf2 ON g.sender_id = rf2.receiver_id AND g.receiver_id = rf2.sender_id
WHERE rf1.time_approved IS NOT NULL
    AND rf2.time_approved IS NOT NULL
    AND rf1.time_approved > g.time
    AND rf2.time_approved > g.time;


