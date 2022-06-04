add_library(core
        src/Neunet.cpp
        src/Neuron.cpp
        Exception.hpp
        src/ActivationFunction.cpp
        functions/BinaryFunction.hpp
        functions/LinearFunction.hpp
        functions/SigmoidFunction.hpp
        functions/HyperbolicTangentFunction.hpp
        functions/ReLuFunction.hpp
        mentors/backprop/src/BackpropMentor.cpp TrainingEpoch.hpp functions/MseFunction.hpp functions/RootMseFunction.hpp functions/ArctanFunction.hpp functions/BiasFunction.hpp)
set_target_properties(core PROPERTIES LINKER_LANGUAGE CXX)