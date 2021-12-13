#pragma once
#define DMX_MAXCHANNEL 512

#include <QtWidgets/QMainWindow>
#include <QTimer>
#include <qdebug.h>
#include <Windows.h>
#include "ui_DMX.h"
#include "DasHard.h"

class DMX : public QMainWindow {
    Q_OBJECT

	public:

		DMX( QWidget *parent = Q_NULLPTR );
		HINSTANCE g_dasusbdll;

		typedef int(*DASHARDCOMMAND)(int, int, unsigned char*);
		DASHARDCOMMAND DasUsbCommand;

		int interface_open;
		unsigned char dmxBlock[512];

	public slots:

		void Update( );
		void ResetDMX1( );
		void ResetDMX2( );
		void ResetDMX3( );
		void Auto( );
		void Random( );
	private:
		Ui::DMXClass ui;
};
