/*
  Programming Exercise 2
  Captain - the main function can or has to:
    He can order cleaning crew to clean and does not have to wait
    on this command until it is done.

    He can order to full speed ahead and have to wait until the
    engine crew finish the command.

    He can order stop command and have to wait until the engine
    crew finish the command.
*/

#include <thread>
#include <iostream>

enum Command {Clean = 1, FullSpeed = 2, Stop = 3, Exit = 100, Unknown = 500};

/*
  Overloading the stream extraction operator to allow a user
  to enter the command of Command enumeration.
  enum command passed by reference to store the user input
  Note the use of underlying_type_t.
*/
std::istream &operator>>(std::istream &is, Command &command) 
{
  // int user_input;   // Will also work
  std::underlying_type_t<Command> user_input;
  is >> user_input;

  switch (user_input) 
  {
    case Clean:       
    case FullSpeed:
    case Stop:
    case Exit:
      command = Command(user_input);  // Store the user input with casting to avoid the error in the assignment
      break;
    default:                   
      command = Unknown;
  }

  return is;
}

/*
  Overloading the insertion operator to insert the
  string representation of the provided Command
  parameter into the output string
*/

std::ostream &operator<<(std::ostream &os, const Command &command)
{
  switch (command)
  {
    case Clean:
      os << "Clean";
      break;
    case FullSpeed:
      os << "FullSpeed";
      break;
    case Stop:
      os << "Stop";
      break;
    case Exit:
      os << "Exit";
      break;
    case Unknown:
      os << "Unknown command";
    break;
    default:
      break;
  }

  return os;
}

void Cleaners() 
{
  std::cout << "cleaning..." << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(5000));
  std::cout << "cleaning is done!!!" << std::endl;
}

void EngineCrewFullSpeed() 
{
  std::cout << "Starting full speed..." << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));
  std::cout << "full speed is done!!!" << std::endl;
}

void EngineCrewStop()
{
  std::cout << "Starting stopping..." << std::endl;
  std::this_thread::sleep_for(std::chrono::milliseconds(6000));
  std::cout << "Stopped is done!!!" << std::endl;
}

// Captain
int main() 
{
  bool run = true;
  while (run) 
  {
    Command command;
    std::cout << "Enter the Captain's command: ";
    std::cin >> command;
    std::cout << "Entered command: " << command << std::endl;

    switch (command) 
    {
      case Clean:
      { 
        std::thread cleaners{ Cleaners };
        cleaners.detach();
        break;
      }
      case FullSpeed:
      { 
        std::thread engine_crew{ EngineCrewFullSpeed };
        engine_crew.join();
        break;
      }
      case Stop:
      { 
        std::thread engine_crew{ EngineCrewStop };
        engine_crew.join();
        break;
      }
      case Exit:
      {
        run = false;
        break;
      }
      case Unknown:
      {
        std::cout << "Invalid command, please try a new command" << std::endl;
      }
    }
  }

  return 0;
}