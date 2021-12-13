#include "DMX.h"

DMX::DMX( QWidget *parent ) : QMainWindow( parent ) {
    
	
	ui.setupUi(this);

	g_dasusbdll = LoadLibrary(L"DasHard2006.dll");

	if ( g_dasusbdll )
		DasUsbCommand = ( DASHARDCOMMAND )::GetProcAddress((HMODULE)g_dasusbdll, "DasUsbCommand");

	interface_open = DasUsbCommand( DHC_INIT, 0, NULL );

	interface_open = DasUsbCommand( DHC_OPEN, 0, 0 );
	ui.state->setText( QString::number( interface_open ) );


	if ( interface_open > 0 ) {

		for ( int i = 0; i < DMX_MAXCHANNEL + 1; i++ )
			dmxBlock[ i ] = 0;

		DasUsbCommand( DHC_DMXOUT, DMX_MAXCHANNEL, dmxBlock );
	}
}

void DMX::Update() {
	
	//DMX1
	dmxBlock[0]		= ui.Slider1->value();
	ui.Label1->setText( QString::number( dmxBlock[0] ) );

	dmxBlock[1]		= ui.Slider2->value();
	ui.Label2->setText( QString::number( dmxBlock[1] ) );

	dmxBlock[2]		= ui.Slider3->value();
	ui.Label3->setText( QString::number( dmxBlock[2] ) );

	dmxBlock[3]		= ui.Slider4->value();
	ui.Label4->setText( QString::number( dmxBlock[3] ) );

	//DMX2
	dmxBlock[4]		= ui.Slider5->value();
	ui.Label5->setText( QString::number( dmxBlock[4] ) );

	dmxBlock[5]		= ui.Slider6->value();
	ui.Label6->setText( QString::number( dmxBlock[5] ) );

	dmxBlock[6]		= ui.Slider7->value();
	ui.Label7->setText( QString::number( dmxBlock[6] ) );

	dmxBlock[7]		= ui.Slider8->value();
	ui.Label8->setText( QString::number( dmxBlock[7] ) );

	//DMX3
	dmxBlock[8]		= ui.Slider9->value();
	ui.Label9->setText( QString::number( dmxBlock[8] ) );

	dmxBlock[9]		= ui.Slider10->value();
	ui.Label10->setText( QString::number( dmxBlock[9] ) );
	
	dmxBlock[10]	= ui.Slider11->value();
	ui.Label11->setText( QString::number( dmxBlock[10] ) );

	dmxBlock[11]	= ui.Slider12->value();
	ui.Label12->setText( QString::number( dmxBlock[11] ) );

	DasUsbCommand( DHC_DMXOUT, DMX_MAXCHANNEL, dmxBlock );
}


void DMX::ResetDMX1() {

	dmxBlock[ 0 ] = 0;
	dmxBlock[ 1 ] = 0;
	dmxBlock[ 2 ] = 0;
	dmxBlock[ 3 ] = 0;

	ui.Slider1->setValue( 0 );
	ui.Slider2->setValue( 0 );
	ui.Slider3->setValue( 0 );
	ui.Slider4->setValue( 0 );

	ui.Label1->setText( QString::number( 0 ) );
	ui.Label2->setText( QString::number( 0 ) );
	ui.Label3->setText( QString::number( 0 ) );
	ui.Label4->setText( QString::number( 0 ) );
}

void DMX::ResetDMX2() {

	dmxBlock[4] = 0;
	dmxBlock[5] = 0;
	dmxBlock[6] = 0;
	dmxBlock[7] = 0;

	ui.Slider5->setValue(0);
	ui.Slider6->setValue(0);
	ui.Slider7->setValue(0);
	ui.Slider8->setValue(0);

	ui.Label5->setText( QString::number( 0 ) );
	ui.Label6->setText( QString::number( 0 ) );
	ui.Label7->setText( QString::number( 0 ) );
	ui.Label8->setText( QString::number( 0 ) );
}

void DMX::ResetDMX3() {

	dmxBlock[8]  = 0;
	dmxBlock[9]  = 0;
	dmxBlock[10] = 0;
	dmxBlock[11] = 0;

	ui.Slider9->setValue( 0 );
	ui.Slider10->setValue( 0 );
	ui.Slider11->setValue( 0 );
	ui.Slider12->setValue( 0 );

	ui.Label9->setText( QString::number( 0 ) );
	ui.Label10->setText( QString::number( 0 ) );
	ui.Label11->setText( QString::number( 0 ) );
	ui.Label12->setText( QString::number( 0 ) );
}


void DMX::Auto() {

	QTimer *timer = new QTimer( this );
	connect(timer, &QTimer::timeout, this, &DMX::Random );
	timer->start( 10 );
}

void DMX::Random( ) {

	int channel = rand() % 12 + 1;
	int value	= rand() % 255 + 1;

	dmxBlock[ channel ] = value;

	DasUsbCommand( DHC_DMXOUT, DMX_MAXCHANNEL, dmxBlock );
}


