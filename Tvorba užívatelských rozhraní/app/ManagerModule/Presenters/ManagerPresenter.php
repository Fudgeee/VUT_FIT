<?php
/**
 * @brief manager presenter
 *
 * @authors Marián Backa (xbacka01)
 */
declare(strict_types=1);

namespace App\ManagerModule\Presenters;

use App\ManagerModule\Model\ManagerModel;

use Nette;
use Nette\Application\UI\Form;

final class ManagerPresenter extends  \App\CoreModule\Presenters\LogedPresenter
{

    private ManagerModel $DBM;
	public function __construct(ManagerModel $DBM)
	{
        $this->DBM=$DBM;
	}

	public function renderDefault(int $page=1,string $orderBy="datumZ",string $filtr="waiting",int $itemsPerPage=5)
	{		
		$this->template->pg=$page;

		$this->template->ob=$orderBy;

			
		$this->template->ft=$filtr;
		$this->template->ipp=$itemsPerPage;

		$this->template->reservations= $this->DBM->getReservations($page,$this->template->ob,$filtr,$itemsPerPage);

		$this->template->pageN=($this->template->reservations->count('*')/$itemsPerPage)+1;
	}

	protected function createComponentParseResForm(): Form
	{
		$form = new Form;
		

		$form->addSubmit('accept', 'Přijmout')->onClick[] = [$this, 'acceptPressed'];
		$form->addSubmit('denied', 'Zamítnout')->onClick[] = [$this, 'deniedPressed'];

		return $form;
	}
	public function acceptPressed(Form $form, \stdClass $values)
	{
		$values = $form->getHttpData($form::DATA_TEXT, 'sel[]');
	
		foreach ($values as $value ) 
		{
			$this->DBM->reservationAccept(intval($value));
		}

	}
	public function deniedPressed(Form $form, \stdClass $values)
	{
		$values = $form->getHttpData($form::DATA_TEXT, 'sel[]');
	
		foreach ($values as $value ) 
		{
			$this->DBM->reservationReject(intval($value));
		}

	}

}	
