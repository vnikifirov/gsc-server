cmake_minimum_required(VERSION 3.5)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake/CMakePCHCompiler)
project(gsc CXX CXXPCH)

set(MODEL_SOURCE_FILES
        src/view/api/Endpoint.C
        src/view/api/Http_status.C
        src/common/format.C
        src/common/paths.C
        src/common/Media_type_registry.C
        src/view/api/Request_body.C
        src/view/api/Request_handler.C
        src/view/api/resources.C
        src/view/api/Result_array.C
        src/model/specializations.h
        src/model/auth/Auth_token.C
        src/model/auth/User.C
        src/model/auth/User_database.C
        src/model/game/Dictionary.C
        src/model/game/User_stats.C
        src/model/Abstract_evaluation.C
        src/model/Assignment.C
        src/model/Eval_item.C
        src/model/Exam_grade.C
        src/model/File_data.C
        src/model/File_meta.C
        src/model/Grader_eval.C
        src/model/Partner_request.C
        src/model/Permalink.C
        src/model/Self_eval.C
        src/Session.C
        src/model/Submission.C)

set(SOURCE_FILES
        src/gscd.C
        ${MODEL_SOURCE_FILES}
        src/Application_controller.C
        src/Navigate.h
        src/view/Abstract_file_view.C
        src/view/Accelerator_button.C
        src/view/Accelerator_text.C
        src/view/Admin_response_widget.C
        src/view/Assignments_view.C
        src/view/Admin_view.C
        src/view/Base_eval_item_widget.C
        src/view/List_eval_item_widget.C
        src/view/Single_eval_item_widget.C
        src/view/Admin_eval_item_widget.C
        src/view/Self_eval_item_widget.C
        src/view/Review_eval_item_widget.C
        src/view/Confirmation_dialog.C
        src/view/Date_time_edit.C
        src/view/Edit_assignment_view.C
        src/view/Error_view.C
        src/view/Explanation_view_widget.C
        src/view/File_list_widget.C
        src/view/File_manager_view.C
        src/view/File_viewer_widget.C
        src/view/Held_back_view.C
        src/view/Grading_stats_view.C
        src/view/Grading_view.C
        src/view/Main_view.C
        src/view/Unit_line_edit.C
        src/view/User_suggester.C
        src/view/Evaluation_view.C
        src/view/Explanation_edit_widget.C
        src/view/Notification.C
        src/view/Partner_notifications_widget.C
        src/view/Response_widget.C
        src/view/Submission_owner_widget.C
        src/view/Submissions_view.C
        src/view/game/HangmanWidget.C
        src/view/game/HighScoresWidget.C
        src/view/game/ImagesWidget.C
        src/view/game/LettersWidget.C
        src/view/game/WordWidget.C)

find_package(Boost REQUIRED COMPONENTS system filesystem)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})

set(LIBRARIES
    wt wtdbo wtdbopostgres # wtdbosqlite3
    ${Boost_LIBRARIES})

add_executable(gscd ${SOURCE_FILES})
target_precompiled_header(gscd src/common/prefix.h)
target_link_libraries(gscd wthttp ${LIBRARIES})

add_executable(gscd-fcgi ${SOURCE_FILES})
target_link_libraries(gscd-fcgi wtfcgi ${LIBRARIES})

add_executable(gscauth src/gscauth.C ${MODEL_SOURCE_FILES})
target_link_libraries(gscauth ${LIBRARIES})

set_target_properties(gscd gscd-fcgi gscauth PROPERTIES
        CXX_STANDARD            14
        CXX_STANDARD_REQUIRED   On
        CXX_EXTENSIONS          Off)

