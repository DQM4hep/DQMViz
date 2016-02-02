  /// \file DQMMonitoringController.h
/*
 *
 * DQMMonitoringController.h header template automatically generated by a class generator
 * Creation date : sam. oct. 10 2015
 *
 * This file is part of DQM4HEP libraries.
 * 
 * DQM4HEP is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * based upon these libraries are permitted. Any copy of these libraries
 * must include this copyright notice.
 * 
 * DQM4HEP is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with DQM4HEP.  If not, see <http://www.gnu.org/licenses/>.
 * 
 * @author Remi Ete
 * @copyright CNRS , IPNL
 */


#ifndef DQMMONITORINGCONTROLLER_H
#define DQMMONITORINGCONTROLLER_H

// -- qt headers
#include <QObject>
#include <QColor>
#include <QMap>
#include <QIcon>

// -- dqm4hep headers
#include "dqm4hep/DQMLogger.h"
#include "dqm4hep/vis/DQMGuiMonitorElement.h"
#include "dqm4hep/DQMMessaging.h"

namespace dqm4hep
{

class DQMMonitoring;
class DQMMonitorElementClient;
class DQMGuiMonitorElementClient;
class DQMCanvasArea;
class DQMCanvas;

/** DQMMonitoringController class
 */ 
class DQMMonitoringController : public QObject, public DQMLogger
{
	Q_OBJECT

	typedef std::map<std::string, DQMGuiMonitorElementClient*> DQMGuiMonitorElementClientMap;

public:
	/** Constructor
	 */
	DQMMonitoringController(DQMMonitoring *pMonitoring);

	/** Destructor
	 */
	~DQMMonitoringController();

	/** Get the monitoring instance
	 */
	DQMMonitoring *getMonitoring() const;

	//
	// Logging interface
	//
	/** Log a message in the application. Log level is 'MESSAGE'
	 */
	void log(const std::string &message);

	/** Log in the logger with a log level
	 */
	void log(LogLevel level, const std::string &message);

	//
	// Monitor element client interface
	//
	/** Create a monitor element client from the collector name.
	 *  Act as a factory method. The client is not registered.
	 *  To get a registered client, use getClient(n) instead
	 */
	DQMGuiMonitorElementClient *createClient(const std::string &collectorName);

	/** Get a registered client. If the client is not registered,
	 *  it is created and added on the fly to the list of registered clients
	 */
	DQMGuiMonitorElementClient *getClient(const std::string &collectorName);

	/** Find a client. Returns NULL is not registered
	 */
	DQMGuiMonitorElementClient *findClient(const std::string &collectorName);

	/** Remove a client from the application. Does nothing if the client is not found
	 */
	void removeClient(const std::string &collectorName);

	/** Fill the model and the view view empty monitor elements.
	 *  Empty monitor elements are created. If  draw action is requested, a 'no viz' canvas will be drawn
	 */
	void createEmptyMonitorElements(const std::string &collectorName, const DQMMonitorElementInfoList &nameList);

	/** Subscribe to monitor elements of the target collector
	 */
	void subscribe(const std::string &collectorName, const DQMMonitorElementRequest &request);

	/** Un-subscribe to monitor elements of the target collector
	 */
	void unsubscribe(const std::string &collectorName, const DQMMonitorElementRequest &request);

public slots:
	/** Send a query to the all collectors
	 *  to send back the subscribed monitor elements
	 */
	void querySubscribedMonitorElements();

public:
	/** Send a query to the target collector
	 *  to send back the subscribed monitor elements
	 */
	void querySubscribedMonitorElements(const std::string &collectorName);

	/** Send a query to the target collector to subscribe to
	 *  the element list (if not done yet) and
	 *  send back the monitor elements in the request
	 */
	void querySubscribedMonitorElements(const std::string &collectorName, const DQMMonitorElementRequest &request);

	/** Un-subscribe to all monitor elements of the target collector
	 */
	void unsubscribe(const std::string &collectorName);

	/** Set the update mode of the target collector
	 */
	void setUpdateMode(bool updateMode);

	/** Get the update mode
	 */
	bool getUpdateMode() const;

	/** Send a query to the collector to first subscribed to the element if
	 *  not done yet, then to send back the element if collected on the server
	 */
	void queryUpdate(DQMGuiMonitorElement *pMonitorElement);

	/** Send a query to the collector to first subscribed to the elements if
	 *  not done yet, then to send back the elements if collected on the server
	 */
	void queryUpdate(const DQMGuiMonitorElementList &monitorElementList);

private slots:
	/** Call back method called by monitor element clients
	 *  when a publication is received
	 */
	void receiveMonitorElementPublication(const DQMMonitorElementPublication &publication);

	/** Send the list of subscribed elements to the collector.
	 *  This is usually called when the server is restarted
	 *  after a shutdown, a manual restart or a crash.
	 *  Send also the update mode
	 */
	void handleServerStartup();

	/** Send the list of subscribed elements to the collector.
	 *  This is usually called when the server is restarted
	 *  after a shutdown, a manual restart or a crash.
	 *  Send also the update mode
	 */
	void handleServerShutdown();

public:
	//
	// Utility functions
	//
	/** Get the color associated to the data quality
	 */
	QColor getColor(DQMQuality quality) const;

	/** Get the icon associated to the data quality
	 */
	QIcon getIcon(DQMQuality quality) const;

public slots:
	//
	// Gui specific methods
	//
	/** Open a file from a file dialog.
	 *  This will clear the current view and
	 *  model and reload a new one.
	 */
	void openFile();

	/** Workhorse of the openfile() method
	 */
	void openFile(const std::string &fileName);

	/** Open a file dialog and save the
	 *  current view and model to the target file.
	 */
	void saveAs();

	/** Workhorse of the saveAs() method
	 */
	void saveAs(const std::string &fileName) const;

	/** Open a browser widget in a separate window.
	 *  The browser is deleted on close action
	 */
	void openBrowser();

	/** Open about DQM4HEP pop up dialog
	 */
	void aboutDQM4HEP();

	/** Open the doxygen documentation (if exists) in the default web browser
	 */
	void openDoxygenDoc();

	/** Open user guide (pdf) in the default pdf reader
	 */
	void openUserGuide();

	/** Open the DQM4HEP github page in the default web browser
	 */
	void openGithubPage();

	/** Open the DQM4HEP issues github page in the default web browser
	 */
	void openIssuesPage();

	/** Open a monitor element info widget in a dialog.
	 *  The tab is set "me info"
	 */
	void openMonitorElementInfo(DQMGuiMonitorElement *pMonitorElement) const;

	/** Open a monitor element info widget in a dialog.
	 *  The tab is set "qtest results"
	 */
	void openQualityTestResults(DQMGuiMonitorElement *pMonitorElement) const;

	/** Fork a process and open the monitor element in root canvas.
	 *  By doing this, the gui client becomes the ROOT one and
	 *  the monitor element in the ROOT process won't be updated.
	 */
	void openInROOTWindow(DQMGuiMonitorElement *pMonitorElement) const;

	/** Save all the canvases of the canvas area in a file
	 *  Different file format available. See implementation.
	 */
	void saveAs(DQMCanvasArea *pCanvasArea);

	/** Save the canvas in a file
	 *  Different file format available. See implementation.
	 */
	void saveAs(DQMCanvas *pCanvas);

	//
	// Clear methods and quit()
	//
	/** Clear the controller.
	 *  This will remove all client connections.
	 *  The view and model are not clear.
	 *  Use clearViewAndModel() to clear only the model and view
	 *  or use clearMonitoring() to clear the model, view and controller.
	 */
	void clear();

	/** Clear the model and view of the monitoring system.
	 *
	 *  The clients update mode is set to false, disabling
	 *  automatic updates. The client connections are not
	 *  removed. Use clearMonitoring() to also clear the
	 *  client connections. Use clear() to clear only the
	 *  client connections and keep the view and model
	 */
	void clearViewAndModel();

	/** Clear the model, view and controller
	 */
	void clearMonitoring();

	/** Exit the monitoring application.
	 *  Clear the monitoring and exit the Qt application
	 */
	void quit();

private:

	DQMMonitoring                   *m_pMonitoring;
	bool                             m_updateMode;
	DQMGuiMonitorElementClientMap    m_clientMap;
	QMap<LogLevel, QString>          m_logLevelToTextMap;
};

} 

#endif  //  DQMMONITORINGCONTROLLER_H
