/**
 * 基本クラス.
 * 全てのクラスの継承元となるクラスです.
 */

#include "BaseClass.h"

/**
 * コンストラクター.
 * 全クラスに共通するクラスの初期処理を行います.
 */
BaseClass::BaseClass() {
}

/**
 * デストラクター.
 * 全クラスに共通するクラスの終了処理を行います.
 */
BaseClass::~BaseClass() {
}

/**
 * 初期処理.
 * 全クラスに共通する初期処理を行います.
 */
void BaseClass::initialize() {
}

/**
 * 終了処理.
 * 全クラスに共通する終了処理を行います.
 */
void BaseClass::finalize() {
}
