<?php
namespace App\LoginModule\Model;
use Nette\Security\IAuthorizator;
use Nette\Security\Permission;

class AuthorizatorFactory
{
	public static function create(): IAuthorizator
	{
		$acl = new Permission();
		$acl->addRole('guest');
        $acl->addRole('registered', 'guest'); 
        $acl->addRole('knihovnik', 'guest'); 
        $acl->addRole('distributor', 'guest'); 
		$acl->addRole('admin', ['knihovnik','distributor','registered']); 

		$acl->addResource('Knihovna');
		$acl->allow('knihovnik', 'Knihovna');

		$acl->addResource('Knihy');
		$acl->allow('distributor', 'Knihy');
		$acl->allow('knihovnik', 'Knihy');

		$acl->addResource('AdminPage');
		$acl->allow('admin', 'AdminPage');

		$acl->addResource('Orders');
		$acl->allow('knihovnik', 'Orders');

		$acl->addResource('OrdersDView');
		$acl->allow('distributor', 'OrdersDView');

		$acl->addResource('OrderMix');
		$acl->allow('distributor', 'OrderMix');
		$acl->allow('knihovnik', 'OrderMix');

		$acl->allow('knihovnik', 'Orders', 'add');

		$acl->addResource('UserBorrow');
		$acl->allow('registered', 'UserBorrow');

		$acl->addResource('KnihovnikBorrow');
		$acl->allow('knihovnik', 'KnihovnikBorrow');


		return $acl;
	}
}