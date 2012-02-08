#ifndef TEST_APP_HPP
#define TEST_APP_HPP

#include <string>
#include <GGE/Core/classes/App.hpp>

class TestApp : public GGE::App
{
public:
	/**
	 * Constructor de la aplicacion.
	 */
	TestApp(const std::string TheTitle = "Test");

	/**
	 * Destructor
	 */
	virtual ~TestApp();

protected:
	/**
	 * Init se encarga de inicializar la aplicacion
	 */
	virtual void Init(void); 

}; // Class TestApp

#endif //TEST_APP_HPP