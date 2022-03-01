<?php
/**
 * @brief  borrow presenter
 *
 * @authors Jakub Komárek (xkomar33)
 */
declare(strict_types=1);

namespace App\BorowModule\Presenters;
use App\BorowModule\Model\BorowModel;

use Nette;
use Nette\Application\UI\Form;

final class BorowPresenter extends  \App\CoreModule\Presenters\LogedPresenter
{

    private BorowModel $BM;
	public function __construct(BorowModel $BM)
	{
        $this->BM=$BM;
	}

	public function actionDefault()
    {
	}
	protected function createComponentRezervateForm(): Form
	{
		$form = new Form;
		$actualDate=date("Y-m-d\TH:i");
		$shiftDate=date("Y-m-d\TH:i", strtotime('+4 hours', strtotime($actualDate)));
		$cond=date("Y-m-d\TH:i", strtotime('-1 hours', strtotime($actualDate)));

		$form->getElementPrototype()->class('ajax');

		$form->addText('od', 'Od')->setHtmlType('datetime-local')
			->setDefaultValue( $actualDate)
			->setHtmlAttribute('min',$cond );

		$form->addText('do', 'Do')->setHtmlType('datetime-local')
			->setDefaultValue($shiftDate)
			->setHtmlAttribute('min', $cond);
			

		$form->addSelect('pohon', 'Pohon:', ['libovolny'=>'Libovolný','spalovaci'=>'Spalovací','elektricky'=>'Elektrický'])
			->setDefaultValue('libovolny');
		$form->addSelect('prevodovka', 'Převodovka:', ['all'=>'Libovoná','manual'=>'Manuální','automat'=>'Automatická'])
			->setDefaultValue('all');
		$form->addInteger('mist', 'Míst')
			->setDefaultValue(1)
			->addRule($form::RANGE, 'Úroveň musí být v rozsahu mezi %d a %d.', [1, 100]);
		$form->addSelect('dojezd', 'Dojezd:', ['0'=>'<100','150'=>'150','200'=>'200','300'=>'300','400'=>'400','500'=>'>500'])
			->setDefaultValue('0');

		$form->addSubmit('hledat','Hledej')->onClick[] = [$this, 'searchPressed'];
		$form->addSubmit('rezervovat','Rezervovat')->onClick[] = [$this, 'reservatePressed'];
		$form->addProtection();
		
		return $form;
	}

	public function reservatePressed(Form $form, \stdClass $outputVals)
	{
		$values = $form->getHttpData($form::DATA_TEXT, 'sel[]');
	
		foreach ($values as $value ) 
		{
			$this->BM->reservationAdd($this->getUser()->getIdentity()->getId(),intval($value),$outputVals->od,$outputVals->do);
			break;
		}
		
		$this->redirect(":DashBoard:DashBoard:");

	}

	public function searchPressed(Form $form, \stdClass $values)
	{
		$this->template->cars=$this->BM->getCars($values);
	}

}
