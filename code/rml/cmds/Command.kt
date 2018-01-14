package rml.cmds

import rml.Scope

abstract class Command(parent: Scope?, lineNum: Int, fileId: String) : Scope(parent) {

    private val _lineNum: Int = lineNum
    val lineNum: Int get() = _lineNum

    private val _fileId = fileId
    val fileId: String get() = _fileId

    abstract fun execute(): Var?

}