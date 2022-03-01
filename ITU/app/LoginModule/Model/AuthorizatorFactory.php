<?php
/**
 * @brief  security model
 *
 * @authors Jakub Komárek (xkomar33)
 */
namespace App\LoginModule\Model;
use Nette\Security\IAuthorizator;
use Nette\Security\Permission;

class AuthorizatorFactory
{
	public static function create(): IAuthorizator
	{
		$acl = new Permission();
		$acl->addRole('user');
		$acl->addRole('manager');
		$acl->addResource('managerModule');
		$acl->allow('manager', 'managerModule');

		return $acl;
	}
}