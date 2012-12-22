-- phpMyAdmin SQL Dump
-- version 2.11.9.4
-- http://www.phpmyadmin.net
--
-- Host: oniddb
-- Generation Time: Dec 21, 2012 at 05:17 PM
-- Server version: 5.1.63
-- PHP Version: 5.2.6-1+lenny16

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

--
-- Database: `coreyg-db`
--

-- --------------------------------------------------------

--
-- Table structure for table `user_subs_to`
--

CREATE TABLE IF NOT EXISTS `user_subs_to` (
  `user_id` int(11) NOT NULL,
  `tier_name` varchar(255) DEFAULT NULL,
  KEY `user_id` (`user_id`),
  KEY `tier_name` (`tier_name`)
) ENGINE=InnoDB DEFAULT CHARSET=latin1;

--
-- Dumping data for table `user_subs_to`
--

INSERT INTO `user_subs_to` (`user_id`, `tier_name`) VALUES
(1, 'oi');

--
-- Constraints for dumped tables
--

--
-- Constraints for table `user_subs_to`
--
ALTER TABLE `user_subs_to`
  ADD CONSTRAINT `user_subs_to_ibfk_1` FOREIGN KEY (`user_id`) 
REFERENCES `users` (`user_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  ADD CONSTRAINT `user_subs_to_ibfk_2` FOREIGN KEY (`tier_name`) 
REFERENCES `tiers` (`tier_name`) ON DELETE CASCADE ON UPDATE CASCADE;

