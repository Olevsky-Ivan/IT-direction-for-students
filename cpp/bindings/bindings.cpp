#include "career/quiz.hpp"

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <string>
#include <utility>

namespace py = pybind11;

PYBIND11_MODULE(career_core, module) {
    py::class_<career::QuizQuestion>(module, "QuizQuestion")
        .def(py::init([](std::string id, std::string skill, std::string correctOptionId) {
            return career::QuizQuestion{
                std::move(id),
                std::move(skill),
                std::move(correctOptionId),
            };
        }))
        .def_readwrite("id", &career::QuizQuestion::id)
        .def_readwrite("skill", &career::QuizQuestion::skill)
        .def_readwrite("correct_option_id", &career::QuizQuestion::correctOptionId);

    py::class_<career::SkillLevel>(module, "SkillLevel")
        .def_readonly("skill", &career::SkillLevel::skill)
        .def_readonly("correct", &career::SkillLevel::correct)
        .def_readonly("asked", &career::SkillLevel::asked)
        .def_readonly("level", &career::SkillLevel::level);

    module.def("draw_questions", &career::drawQuestions);
    module.def("score_questions", &career::scoreQuestions);
    module.def("accuracy_note", &career::accuracyNote);
}
