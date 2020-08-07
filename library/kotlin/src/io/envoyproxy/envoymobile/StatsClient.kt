package io.envoyproxy.envoymobile

/**
 * Client used to record timeseries metrics.
 */
interface StatsClient {

  /**
   * @return A counter based on the joined elements.
   */
  fun counter(vararg elements: Element): Counter
}
