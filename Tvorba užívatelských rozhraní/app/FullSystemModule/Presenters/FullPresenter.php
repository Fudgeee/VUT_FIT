<?php
/**
 * @brief dashboard presenter
 *
 * @authors Adrián Matušík (xmatus35)
 */
declare(strict_types=1);

namespace App\FullSystemModule\Presenters;

use App\FullSystemModule\Model\FullModel;
use Nette\Forms\Controls\SubmitButton;

use Nette;
use Nette\Application\UI\Form;

final class FullPresenter extends  \App\CoreModule\Presenters\LogedPresenter
{

    private FullModel $DBM;
	public function __construct(FullModel $DBM)
	{
        $this->DBM=$DBM;
	}

	protected function beforeRender()
    {

    }
	public function renderDefault(): void
	{
		if (!$this->isAjax()) 
		{
			$this->template->list = $this->getWholeList();
			$this->template->count= $this->DBM->getCount();
		}
	}
	private function getWholeList(): array
	{
		return $this->DBM->getUsers()->fetchAll();
	}
	public function handleCountUsers(): void
	{
		$this->template->count= $this->DBM->getCount();
		$this->redrawControl('count');
	}
	public function handleChangeRole(int $id,string $role): void
	{
		$this->DBM->UserRoleSet($id,$role);
		$this->template->list = $this->isAjax()
				? []
				: $this->getWholeList();
		$this->template->list[$id] =  $this->DBM->getUser( $id);
		$this->redrawControl('items');
	}
	public function handleRemove(int $id): void
	{
		$this->DBM->removeUser($id);
		$this->template->list = $this->getWholeList();
		$this->redrawControl('wholeList');
		$this->template->count= $this->DBM->getCount();
		$this->redrawControl('count');
	}
	public function handleVerVer(int $id): void
	{
		$this->DBM->verVer($id);
		$this->template->list[$id] =  $this->DBM->getUser( $id);
		$this->redrawControl('items');
	}
	public function handleUnverVer(int $id): void
	{
		$this->DBM->unverVer($id);
		$this->template->list[$id] =  $this->DBM->getUser( $id);
		$this->redrawControl('items');
	}
}	
