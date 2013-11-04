-- phpMyAdmin SQL Dump
-- version 2.11.9.4
-- http://www.phpmyadmin.net
--
-- Host: oniddb
-- Generation Time: Dec 21, 2012 at 05:16 PM
-- Server version: 5.1.63
-- PHP Version: 5.2.6-1+lenny16

SET SQL_MODE="NO_AUTO_VALUE_ON_ZERO";

--
-- Database: `coreyg-db`
--

-- --------------------------------------------------------

--
-- Table structure for table `tiers`
--

CREATE TABLE IF NOT EXISTS `tiers` (
  `tier_id` int(11) NOT NULL AUTO_INCREMENT,
  `tier_name` varchar(255) NOT NULL,
  `cost` decimal(10,2) NOT NULL,
  `sub_length` int(11) NOT NULL,
  `space_alloted` int(11) NOT NULL,
  PRIMARY KEY (`tier_id`),
  UNIQUE KEY `tier_name` (`tier_name`),
  UNIQUE KEY `cost` (`cost`),
  UNIQUE KEY `sub_length` (`sub_length`),
  UNIQUE KEY `space_alloted` (`space_alloted`)
) ENGINE=InnoDB  DEFAULT CHARSET=latin1 AUTO_INCREMENT=2 ;

--
-- Dumping data for table `tiers`
--

