package rml.cmds

import rml.Context

abstract class Command(parent: Context?, lineNum: Int, fileId: String) : Context(parent) {

    private val _lineNum: Int = lineNum
    val lineNum: Int get() = _lineNum

    private val _fileId = fileId
    val fileId: String get() = _fileId

    abstract fun execute(): Var?

    abstract fun clone(): Command

}