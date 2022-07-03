-- phpMyAdmin SQL Dump
-- version 4.6.6deb5ubuntu0.5
-- https://www.phpmyadmin.net/
--
-- 主機: localhost:3306
-- 產生時間： 2021 年 10 月 30 日 21:49
-- 伺服器版本: 5.7.36-0ubuntu0.18.04.1
-- PHP 版本： 7.2.24-0ubuntu0.18.04.10

SET SQL_MODE = "NO_AUTO_VALUE_ON_ZERO";
SET time_zone = "+00:00";


/*!40101 SET @OLD_CHARACTER_SET_CLIENT=@@CHARACTER_SET_CLIENT */;
/*!40101 SET @OLD_CHARACTER_SET_RESULTS=@@CHARACTER_SET_RESULTS */;
/*!40101 SET @OLD_COLLATION_CONNECTION=@@COLLATION_CONNECTION */;
/*!40101 SET NAMES utf8mb4 */;

--
-- 資料庫： `POS_REP`
--

-- --------------------------------------------------------

--
-- 資料表結構 `member_2`
--

CREATE TABLE `member_2` (
  `time` datetime NOT NULL ON UPDATE CURRENT_TIMESTAMP,
  `lat` double NOT NULL,
  `lng` double NOT NULL,
  `id` int(11) NOT NULL
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- 資料表的匯出資料 `member_2`
--

INSERT INTO `member_2` (`time`, `lat`, `lng`, `id`) VALUES
('2021-10-23 18:19:01', 22.9857066667, 120.220018333, 1),
('2021-10-23 18:19:06', 22.9857066667, 120.220018333, 2),
('2021-10-23 18:19:27', 22.985635, 120.220151667, 3),
('2021-10-23 18:19:32', 22.9856466667, 120.220146667, 4),
('2021-10-23 18:19:37', 22.9856466667, 120.220146667, 5);

--
-- 已匯出資料表的索引
--

--
-- 資料表索引 `member_2`
--
ALTER TABLE `member_2`
  ADD PRIMARY KEY (`id`);

--
-- 在匯出的資料表使用 AUTO_INCREMENT
--

--
-- 使用資料表 AUTO_INCREMENT `member_2`
--
ALTER TABLE `member_2`
  MODIFY `id` int(11) NOT NULL AUTO_INCREMENT, AUTO_INCREMENT=180;
/*!40101 SET CHARACTER_SET_CLIENT=@OLD_CHARACTER_SET_CLIENT */;
/*!40101 SET CHARACTER_SET_RESULTS=@OLD_CHARACTER_SET_RESULTS */;
/*!40101 SET COLLATION_CONNECTION=@OLD_COLLATION_CONNECTION */;
